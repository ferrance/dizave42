qmk clean
qmk compile -e CONVERT_TO=kb2040 -e BIG_OLED=yes
mv ~/qmk_firmware/crkbd_rev1_dizave42_kb2040.uf2 ~/qmk_firmware/crkbd_dizave42_bigoled.uf2
cp ~/qmk_firmware/crkbd_dizave42_bigoled.uf2 .
qmk compile -e CONVERT_TO=kb2040 
mv ~/qmk_firmware/crkbd_rev1_dizave42_kb2040.uf2 ~/qmk_firmware/crkbd_dizave42.uf2
cp ~/qmk_firmware/crkbd_dizave42.uf2 .
