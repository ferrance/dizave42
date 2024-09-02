qmk compile -c -e BIG_OLED=yes
mv ~/qmk_firmware/crkbd_rev1_dizave42.uf2 ~/qmk_firmware/crkbd_dizave42_bigoled.uf2
cp ~/qmk_firmware/crkbd_dizave42_bigoled.uf2 ./firmware
qmk compile -c 
mv ~/qmk_firmware/crkbd_rev1_dizave42.uf2 ~/qmk_firmware/crkbd_dizave42_rp2040.uf2
cp ~/qmk_firmware/crkbd_dizave42_rp2040.uf2 ./firmware
qmk compile -c -e CONVERT_TO=promicro_rp2040
mv ~/qmk_firmware/crkbd_rev1_dizave42_promicro_rp2040.uf2 ~/qmk_firmware/crkbd_dizave42_elitepi.uf2
cp ~/qmk_firmware/crkbd_dizave42_elitepi.uf2 ./firmware
