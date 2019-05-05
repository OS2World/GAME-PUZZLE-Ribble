md disk
md disk\dist
copy ribble\readme.txt disk
copy ribble\history.txt disk
cd bcos2
make -f ribble.mak
make -f install.mak
cd ..
copy levels\* disk\dist
copy bcos2\ribble.exe disk\dist
copy bcos2\install.exe disk
cd disk\dist
del earibble.exe
eautil ribble.exe earibble.exe /S
cd ..\..\help
call makehelp
cd ..
copy ribble.hlp disk\dist
cd disk
del ribble.zip
zip -r -9 ribble *
cd ..
