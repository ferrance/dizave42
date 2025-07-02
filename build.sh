#qmk compile -c -e BIG_OLED=yes
#mv ~/qmk_firmware/crkbd_rev1_dizave42.uf2 ~/qmk_firmware/crkbd_dizave42_bigoled.uf2
#cp ~/qmk_firmware/crkbd_dizave42_bigoled.uf2 ./firmware

# this is for the adafruit kb2040 pinout
qmk compile -c 
mv ~/qmk_firmware/crkbd_rev1_dizave42.uf2 ~/qmk_firmware/crkbd_dizave42_rp2040.uf2
cp ~/qmk_firmware/crkbd_dizave42_rp2040.uf2 ./firmware

# this is for the other pinout that is like $2 on 
# the promicro is deprecated, I'll need to figure out to switch to either sparkfun_pm2040 or rp2040_ce
qmk compile -c -e CONVERT_TO=promicro_rp2040
mv ~/qmk_firmware/crkbd_rev1_dizave42_promicro_rp2040.uf2 ~/qmk_firmware/crkbd_dizave42_elitepi.uf2
cp ~/qmk_firmware/crkbd_dizave42_elitepi.uf2 ./firmware
