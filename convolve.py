import numpy as np
import cv2
from image import Image

def convolve_even(ImSrc, ImDst, mask):
    """
    I have not really understand how it work yet
    """
    width  = int(ImSrc.shape[1])
    height = int(ImSrc.shape[0])

    LEN = mask.shape[0]

    for y in range(height):
        for x in range(width):
            S = mask[0] * ImSrc[y, x]

            for i in range(1, LEN):
                S += mask[i] * ImSrc[y, max(x - i, 0)]
                S += mask[i] * ImSrc[y, min(x + i, width - 1)]
            
            ImDst[y, x] = S
        
def convolve_odd(ImSrc, ImDst, mask):
    """
    This will not change the pixel much if the pixels around it is the same.
    The reason is that the values contributed by 2 symetrical pixels are canceled.
    As you can see, only the outlines of the objects are made to have some ridiculous color
    """
    width  = ImSrc.shape[1]
    height = ImSrc.shape[0]

    LEN = mask.shape[0]

    for y in range(height):
        for x in range(width):
            S = mask[0] * ImSrc[y, x]

            for i in range(1, LEN):
                S += mask[i] * ImSrc[y, max(x - i, 0)]
                S -= mask[i] * ImSrc[y, min(x + i, width - 1)]
            
            ImDst[y, x] = S
        
if __name__ == '__main__':
    mask = np.random.rand((5))

    video_capture = cv2.VideoCapture(0)

    while (1):
        # Capture frame-by-frame
        ret, frame = video_capture.read()
        key = cv2.waitKey(20)

        if (ret == False):  break
        if (key == 27):     break

        frame = cv2.resize(frame, dsize = (100, 100), interpolation=cv2.INTER_CUBIC)

        convolved_frame1 = frame.copy()
        convolved_frame2 = frame.copy()

        convolve_even(frame, convolved_frame1, mask)
        convolve_odd(frame,  convolved_frame2, mask)

        frame = cv2.resize(frame, dsize = (500, 500), interpolation=cv2.INTER_CUBIC)
        convolved_frame1 = cv2.resize(convolved_frame1, dsize = (500, 500), interpolation=cv2.INTER_CUBIC)
        convolved_frame2 = cv2.resize(convolved_frame2, dsize = (500, 500), interpolation=cv2.INTER_CUBIC)

        frame = np.hstack((frame, convolved_frame1, convolved_frame2))

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

        cv2.imshow('Original and convolved images', frame)            


    video_capture.release()
    cv2.destroyAllWindows()


