# help-to-ipf.ps1 - expand help/*.hc into pure IPF source (help/*.ipf)
#
# Replicates the classic makehelp pipeline (sed.form -> cpp -> sed.fix) so
# the .hc sources stay in the readable C-macro form. Output is written in
# codepage 850 for the OS/2 IPF compiler (ipfc).
#
# The pXXX identifiers declared in help.h become numeric panel res ids,
# exactly as cpp did via #include "help.h".
#
# Usage:  powershell -File tools/help-to-ipf.ps1 [base ...]
#         (no args = convert all six languages)

$ErrorActionPreference = 'Stop'

$helpDir = Join-Path $PSScriptRoot '..\help'
$helpDir = [System.IO.Path]::GetFullPath($helpDir)

# --- parse document.h macros ------------------------------------------------
$doc = Get-Content (Join-Path $helpDir 'document.h') | Where-Object { $_ -match '^#define' }
$macros = [ordered]@{}
foreach ($line in $doc) {
  $m = [regex]::Match($line, '^#define\s+([A-Z]+)\(\)\s*(.*)$')
  if ($m.Success) { $macros[$m.Groups[1].Value] = $m.Groups[2].Value; continue }
  $m = [regex]::Match($line, '^#define\s+([A-Z]+)\(([^)]*)\)\s*(.*)$')
  if ($m.Success) {
    $argnames = $m.Groups[2].Value -split ',' | ForEach-Object { $_.Trim() }
    $macros[$m.Groups[1].Value] = @{ args = $argnames; body = $m.Groups[3].Value }
  }
}

# --- parse help.h panel ids ------------------------------------------------
$ids = @{}
foreach ($line in Get-Content (Join-Path $helpDir 'help.h')) {
  $m = [regex]::Match($line, '^#define\s+(p[A-Z0-9_]+)\s+(\d+)')
  if ($m.Success) { $ids[$m.Groups[1].Value] = $m.Groups[2].Value }
}

# --- macro expansion --------------------------------------------------------
function Expand-Macros([string]$text) {
  # repeatedly expand any known NAME(...) calls
  for ($pass = 0; $pass -lt 20; $pass++) {
    $changed = $false
    foreach ($name in $macros.Keys) {
      $def = $macros[$name]
      # find NAME( ... ) with balanced parens, no nesting assumptions
      $re = "(" + [regex]::Escape($name) + ")\s*\("
      $mm = [regex]::Match($text, $re)
      if ($mm.Success) {
        $open = $text.IndexOf('(', $mm.Index)
        $depth = 0
        for ($i = $open; $i -lt $text.Length; $i++) {
          if ($text[$i] -eq '(') { $depth++ }
          elseif ($text[$i] -eq ')') { $depth--; if ($depth -eq 0) { $close = $i; break } }
        }
        if ($i -ge $text.Length) { throw "unbalanced parens in: $text" }
        $argText = $text.Substring($open + 1, $close - $open - 1)
        $before = $text.Substring(0, $mm.Index)
        $after  = $text.Substring($close + 1)
        if ($def -is [string]) {
          $repl = $def            # zero-arg macro
        } else {
          $parts = if ($argText.Trim().Length -eq 0) { @('') } else { @($argText -split ',') }
          $parts = @($parts | ForEach-Object { $_.Trim() })
          if ($parts.Count -ne $def.args.Count) { throw "arg count for ${name}: got $($parts.Count) want $($def.args.Count) in: $text" }
          $repl = $def.body
          for ($k = 0; $k -lt $parts.Count; $k++) {
            $argName = $def.args[$k]
            if ($argName.Length -eq 0) { continue }
            $esc = [regex]::Escape($argName)
            $val = $parts[$k]
            # cpp ## token pasting (##a##, ##a, a##) plus the bare
            # standalone token, in a single pass so inserted values are
            # never re-scanned.
            $pat = "##$esc##|##$esc|$esc##|(?<![A-Za-z0-9_])$esc(?![A-Za-z0-9_])"
            $repl = [regex]::Replace($repl, $pat, $val)
          }
          $repl = $repl.Replace('##', '')
        }
        $text = $before + $repl + $after
        $changed = $true
      }
    }
    if (-not $changed) { break }
  }
  return $text
}

# --- per-line conversion -----------------------------------------------------
function Convert-Hc($lines) {
  $out = New-Object System.Collections.Generic.List[string]
  foreach ($line in $lines) {
    $t = $line
    if ($t -match '^\s*//') { continue }                 # comment line
    if ($t -match '^\s*#\s*include\b') { continue }      # header consumed here
    if ($t -match '^\s*$') { continue }                  # blank line

    # protection (sed.form); order matters
    $t = $t.Replace("'", '!apost!')
    $t = $t.Replace(':', '&colon.')
    $t = $t.Replace('..', '!dotdot!')
    $t = $t.Replace('@', '!at!')
    $t = $t.Replace('\', '!slash!')
    $t = $t.Replace('#', '!hash!')

    $t = Expand-Macros $t

    # numeric panel ids (cpp #include "help.h")
    $t = [regex]::Replace($t, '\bp[A-Z][A-Z0-9_]*\b', {
      param($mm)
      $tok = $mm.Value
      if ($ids.ContainsKey($tok)) { return $ids[$tok] }
      Write-Warning "unresolved panel id $tok"
      return $tok
    })

    # restore (sed.fix)
    $t = $t.Replace('!apost!', "'")
    $t = $t.Replace('!dotdot!', '..')
    $t = $t.Replace('!at!', '@')
    $t = $t.Replace('!slash!', '\')
    $t = $t.Replace('!hash!', '#')

    $out.Add($t)
  }
  return $out
}

$enc = [System.Text.Encoding]::GetEncoding(850)

if ($args.Count -eq 0) {
  $bases = @('ribble-en', 'ribble-es', 'ribble-nl', 'ribble-de', 'ribble-fr', 'ribble-it')
} else {
  $bases = $args
}

foreach ($base in $bases) {
  $hc = Join-Path $helpDir ($base + '.hc')
  if (-not (Test-Path $hc)) { Write-Warning "missing $hc"; continue }
  $lines = Get-Content $hc
  $converted = Convert-Hc $lines
  $ipf = Join-Path $helpDir ($base + '.ipf')
  [System.IO.File]::WriteAllLines($ipf, $converted, $enc)
  Write-Output "$base : $($converted.Count) lines -> $ipf"
}