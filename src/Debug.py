from PIL import Image
import numpy as np
import matplotlib.pyplot as plt

image = Image.open(r"C:\ImgProc\src\feels-strong-man.bmp")
i2 = Image.open(r"C:\ImgProc\src\grayscale.bmp")

arr = np.array(image)
arr2 = np.array(i2)

# Ensure that the images have the same dimensions
assert (arr.shape == arr2.shape)

print(arr)
print("After copy attempt: ")
print(arr2)

image.show()
i2.show()