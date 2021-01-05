def hsv_to_rgb(h, s=1.0, v=1.0):
    h %= 360

    c = v * s
    x = c * (1 - abs((h / 60) % 2 - 1))
    m = v - c

    _R = 0
    _G = 0
    _B = 0

    if 0 <= h < 60:
        _R = c
        _G = x
    elif 60 <= h < 120:
        _R = x
        _G = c
    elif 120 <= h < 180:
        _G = c
        _B = x
    elif 180 <= h < 240:
        _G = x
        _B = c
    elif 240 <= h < 300:
        _R = x
        _B = c
    elif 300 <= h < 360:
        _R = c
        _B = x

    r = int((_R + m) * 255)
    g = int((_G + m) * 255)
    b = int((_B + m) * 255)

    return r, g, b


def rgb_to_hsv(rgb):

    r = rgb[0] / 255.0
    g = rgb[1] / 255.0
    b = rgb[2] / 255.0

    cmax = max(r, g, b)
    cmin = min(r, g, b)
    diff = cmax - cmin

    h = 0
    if cmax == cmin:
        h = 0
    elif cmax == r:
        h = (60 * ((g - b) / diff) + 360) % 360
    elif cmax == g:
        h = (60 * ((b - r) / diff) + 120) % 360
    elif cmax == b:
        h = (60 * ((r - g) / diff) + 240) % 360

    if cmax == 0:
        s = 0
    else:
        s = diff / cmax

    v = cmax

    return h, s, v


def rgb_to_color(r, g, b):
    """Convert three 8-bit red, green, blue component values to a single 24-bit
    color value.
    """
    return ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF)


if __name__ == "__main__":

    print(hsv_to_rgb(0))
    print(hsv_to_rgb(120))
    print(hsv_to_rgb(240))
    print(hsv_to_rgb(60))
    print(hsv_to_rgb(180))
    print(hsv_to_rgb(300))
