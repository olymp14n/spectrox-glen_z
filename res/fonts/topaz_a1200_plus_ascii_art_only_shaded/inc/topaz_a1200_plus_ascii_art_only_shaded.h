fw_font_glyph _logoFontGlyphs[] = {
    [32] = {16, 34, 3, 16, -1, 0, 8},
    [33] = {40, 34, 2, 16, 3, 0, 8},
    [34] = {100, 17, 5, 16, 1, 0, 8},
    [35] = {107, 0, 7, 16, 0, 0, 8},
    [39] = {124, 17, 3, 16, 2, 0, 8},
    [40] = {106, 17, 5, 16, 3, 0, 8},
    [41] = {118, 17, 5, 16, 0, 0, 8},
    [42] = {36, 0, 8, 16, 0, 0, 8},
    [43] = {44, 17, 6, 16, 1, 0, 8},
    [44] = {24, 34, 3, 16, 2, 0, 8},
    [45] = {63, 0, 8, 16, 0, 0, 8},
    [46] = {55, 34, 2, 16, 3, 0, 8},
    [47] = {0, 0, 8, 16, 0, 0, 8},
    [55] = {51, 17, 6, 16, 1, 0, 8},
    [58] = {46, 34, 2, 16, 3, 0, 8},
    [59] = {12, 34, 3, 16, 2, 0, 8},
    [60] = {112, 17, 5, 16, 3, 0, 8},
    [61] = {9, 0, 8, 16, 0, 0, 8},
    [62] = {6, 34, 5, 16, 0, 0, 8},
    [63] = {79, 17, 6, 16, 1, 0, 8},
    [76] = {58, 17, 6, 16, 1, 0, 8},
    [79] = {65, 17, 6, 16, 1, 0, 8},
    [89] = {45, 0, 8, 16, 0, 0, 8},
    [92] = {90, 0, 8, 16, 0, 0, 8},
    [93] = {72, 17, 6, 16, 0, 0, 8},
    [94] = {115, 0, 7, 16, 0, 0, 8},
    [95] = {18, 0, 8, 16, 0, 0, 8},
    [96] = {20, 34, 3, 16, 3, 0, 8},
    [105] = {28, 34, 3, 16, 3, 0, 8},
    [106] = {0, 34, 5, 16, 1, 0, 8},
    [108] = {32, 34, 3, 16, 3, 0, 8},
    [111] = {86, 17, 6, 16, 1, 0, 8},
    [123] = {99, 0, 7, 16, 1, 0, 8},
    [124] = {43, 34, 2, 16, 3, 0, 8},
    [125] = {8, 17, 7, 16, 0, 0, 8},
    [126] = {0, 17, 7, 16, 0, 0, 8},
    [161] = {49, 34, 2, 16, 3, 0, 8},
    [164] = {37, 17, 6, 16, 1, 0, 8},
    [166] = {52, 34, 2, 16, 3, 0, 8},
    [168] = {93, 17, 6, 16, 1, 0, 8},
    [171] = {72, 0, 8, 16, 0, 0, 8},
    [172] = {54, 0, 8, 16, 0, 0, 8},
    [173] = {16, 17, 6, 16, 1, 0, 8},
    [175] = {81, 0, 8, 16, 0, 0, 8},
    [176] = {23, 17, 6, 16, 1, 0, 8},
    [177] = {30, 17, 6, 16, 1, 0, 8},
    [180] = {123, 0, 4, 16, 1, 0, 8},
    [183] = {58, 34, 2, 16, 3, 0, 8},
    [184] = {36, 34, 3, 16, 2, 0, 8},
    [187] = {27, 0, 8, 16, 0, 0, 8},
    [85] = {61, 34, 8, 16, 0, 0, 8},
    [77] = {84, 34, 8, 16, 0, 0, 8},
    [69] = {76, 34, 3, 16, 3, 0, 8},
    [74] = {103, 34, 5, 16, 1, 0, 8},
    [83] = {93, 34, 6, 16, 1, 0, 8},
    [73] = {80, 34, 3, 16, 3, 0, 8},
    [88] = {70, 34, 2, 16, 3, 0, 8},
    [86] = {73, 34, 2, 16, 3, 0, 8},
    [70] = {106, 34, 8, 16, 0, 0, 8},
    [66] = {115, 34, 8, 16, 0, 0, 8},
};

fw_font_face _logoFontFace = {
    .outline = 0,
    .lineHeight = 16,
    .textureWidth = 128,
    .textureHeight = 64,
    .glyphs = _logoFontGlyphs,
    .numGlyphs = (sizeof(_logoFontGlyphs) / sizeof(_logoFontGlyphs[0])),
};
