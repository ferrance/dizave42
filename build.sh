#qmk compile -c -e BIG_OLED=yes
#mv ~/qmk_firmware/crkbd_rev1_dizave42.uf2 ~/qmk_firmware/crkbd_dizave42_bigoled.uf2
#cp ~/qmk_firmware/crkbd_dizave42_bigoled.uf2 ./firmware

# this is for the adafruit kb2040 pinout
qmk compile -c 
mv ~/qmk_firmware/crkbd_rev1_dizave42.uf2 ~/qmk_firmware/crkbd_dizave42_rp2040.uf2
cp ~/qmk_firmware/crkbd_dizave42_rp2040.uf2 ./firmware

# this is for the other pinout that is like $2 on 
qmk compile -c -e CONVERT_TO=elite_pi
mv ~/qmk_firmware/crkbd_rev1_dizave42_promicro_rp2040.uf2 ~/qmk_firmware/crkbd_dizave42_elitepi.uf2
cp ~/qmk_firmware/crkbd_dizave42_elitepi.uf2 ./firmware
