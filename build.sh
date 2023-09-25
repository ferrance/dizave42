qmk clean
qmk compile -e CONVERT_TO=kb2040 -e BIG_OLED=yes
mv ../../../../crkbd_rev1_dizave42_kb2040.uf2 ./crkbd_dizave42_bigoled.uf2
qmk compile -e CONVERT_TO=kb2040 
mv ../../../../crkbd_rev1_dizave42_kb2040.uf2 ./crkbd_dizave42.uf2
