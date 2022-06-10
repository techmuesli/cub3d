from PIL import Image
import numpy as np
from numpy import asarray
import pandas as pd 

image = Image.open('F:/maze/Totally_not_a_Rickroll_QR_code.png')
  
# summarize some details about the image
print(image.format)
print(image.size)
print(image.mode)

numpydata = asarray(image)

for y in range(0, image.size[1], 7):
    for x in range(0, image.size[0], 7):
        if numpydata[x,y,0] == 0:
            print("1", end='');
        if numpydata[x,y,0] == 255:
            print("0", end='')
    print("\n", end='')



# pd.DataFrame(numpydata).to_csv("F:/maze/qrcode.csv", header=None, index=None)
