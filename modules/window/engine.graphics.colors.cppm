export module engine.graphics.colors;
import engine.graphics;

export namespace engine::graphics::color {

#define UINT2FLOAT(r) (static_cast<float>(r) / 250.0f)

  [[maybe_unused]] constexpr Color aliceblue = {UINT2FLOAT(240), UINT2FLOAT(248), UINT2FLOAT(255)};
  [[maybe_unused]] constexpr Color antiquewhite = {UINT2FLOAT(250), UINT2FLOAT(235), UINT2FLOAT(215)};
  [[maybe_unused]] constexpr Color aqua = {UINT2FLOAT(0), UINT2FLOAT(255), UINT2FLOAT(255)};
  [[maybe_unused]] constexpr Color aquamarine = {UINT2FLOAT(127), UINT2FLOAT(255), UINT2FLOAT(212)};
  [[maybe_unused]] constexpr Color azure = {UINT2FLOAT(240), UINT2FLOAT(255), UINT2FLOAT(255)};
  [[maybe_unused]] constexpr Color beige = {UINT2FLOAT(245), UINT2FLOAT(245), UINT2FLOAT(220)};
  [[maybe_unused]] constexpr Color bisque = {UINT2FLOAT(255), UINT2FLOAT(228), UINT2FLOAT(196)};
  [[maybe_unused]] constexpr Color black = {UINT2FLOAT(0), UINT2FLOAT(0), UINT2FLOAT(0)};
  [[maybe_unused]] constexpr Color blanchedalmond = {UINT2FLOAT(255), UINT2FLOAT(235), UINT2FLOAT(205)};
  [[maybe_unused]] constexpr Color blue = {UINT2FLOAT(0), UINT2FLOAT(0), UINT2FLOAT(255)};
  [[maybe_unused]] constexpr Color blueviolet = {UINT2FLOAT(138), UINT2FLOAT(43), UINT2FLOAT(226)};
  [[maybe_unused]] constexpr Color brown = {UINT2FLOAT(165), UINT2FLOAT(42), UINT2FLOAT(42)};
  [[maybe_unused]] constexpr Color burlywood = {UINT2FLOAT(222), UINT2FLOAT(184), UINT2FLOAT(135)};
  [[maybe_unused]] constexpr Color cadetblue = {UINT2FLOAT(95), UINT2FLOAT(158), UINT2FLOAT(160)};
  [[maybe_unused]] constexpr Color chartreuse = {UINT2FLOAT(127), UINT2FLOAT(255), UINT2FLOAT(0)};
  [[maybe_unused]] constexpr Color chocolate = {UINT2FLOAT(210), UINT2FLOAT(105), UINT2FLOAT(30)};
  [[maybe_unused]] constexpr Color coral = {UINT2FLOAT(255), UINT2FLOAT(127), UINT2FLOAT(80)};
  [[maybe_unused]] constexpr Color cornflowerblue = {UINT2FLOAT(100), UINT2FLOAT(149), UINT2FLOAT(237)};
  [[maybe_unused]] constexpr Color cornsilk = {UINT2FLOAT(255), UINT2FLOAT(248), UINT2FLOAT(220)};
  [[maybe_unused]] constexpr Color crimson = {UINT2FLOAT(220), UINT2FLOAT(20), UINT2FLOAT(60)};
  [[maybe_unused]] constexpr Color cyan = {UINT2FLOAT(0), UINT2FLOAT(255), UINT2FLOAT(255)};
  [[maybe_unused]] constexpr Color darkblue = {UINT2FLOAT(0), UINT2FLOAT(0), UINT2FLOAT(139)};
  [[maybe_unused]] constexpr Color darkcyan = {UINT2FLOAT(0), UINT2FLOAT(139), UINT2FLOAT(139)};
  [[maybe_unused]] constexpr Color darkgoldenrod = {UINT2FLOAT(184), UINT2FLOAT(134), UINT2FLOAT(11)};
  [[maybe_unused]] constexpr Color darkgray = {UINT2FLOAT(169), UINT2FLOAT(169), UINT2FLOAT(169)};
  [[maybe_unused]] constexpr Color darkgreen = {UINT2FLOAT(0), UINT2FLOAT(100), UINT2FLOAT(0)};
  [[maybe_unused]] constexpr Color darkgrey = {UINT2FLOAT(169), UINT2FLOAT(169), UINT2FLOAT(169)};
  [[maybe_unused]] constexpr Color darkkhaki = {UINT2FLOAT(189), UINT2FLOAT(183), UINT2FLOAT(107)};
  [[maybe_unused]] constexpr Color darkmagenta = {UINT2FLOAT(139), UINT2FLOAT(0), UINT2FLOAT(139)};
  [[maybe_unused]] constexpr Color darkolivegreen = {UINT2FLOAT(85), UINT2FLOAT(107), UINT2FLOAT(47)};
  [[maybe_unused]] constexpr Color darkorange = {UINT2FLOAT(255), UINT2FLOAT(140), UINT2FLOAT(0)};
  [[maybe_unused]] constexpr Color darkorchid = {UINT2FLOAT(153), UINT2FLOAT(50), UINT2FLOAT(204)};
  [[maybe_unused]] constexpr Color darkred = {UINT2FLOAT(139), UINT2FLOAT(0), UINT2FLOAT(0)};
  [[maybe_unused]] constexpr Color darksalmon = {UINT2FLOAT(233), UINT2FLOAT(150), UINT2FLOAT(122)};
  [[maybe_unused]] constexpr Color darkseagreen = {UINT2FLOAT(143), UINT2FLOAT(188), UINT2FLOAT(143)};
  [[maybe_unused]] constexpr Color darkslateblue = {UINT2FLOAT(72), UINT2FLOAT(61), UINT2FLOAT(139)};
  [[maybe_unused]] constexpr Color darkslategray = {UINT2FLOAT(47), UINT2FLOAT(79), UINT2FLOAT(79)};
  [[maybe_unused]] constexpr Color darkslategrey = {UINT2FLOAT(47), UINT2FLOAT(79), UINT2FLOAT(79)};
  [[maybe_unused]] constexpr Color darkturquoise = {UINT2FLOAT(0), UINT2FLOAT(206), UINT2FLOAT(209)};
  [[maybe_unused]] constexpr Color darkviolet = {UINT2FLOAT(148), UINT2FLOAT(0), UINT2FLOAT(211)};
  [[maybe_unused]] constexpr Color deeppink = {UINT2FLOAT(255), UINT2FLOAT(20), UINT2FLOAT(147)};
  [[maybe_unused]] constexpr Color deepskyblue = {UINT2FLOAT(0), UINT2FLOAT(191), UINT2FLOAT(255)};
  [[maybe_unused]] constexpr Color dimgray = {UINT2FLOAT(105), UINT2FLOAT(105), UINT2FLOAT(105)};
  [[maybe_unused]] constexpr Color dimgrey = {UINT2FLOAT(105), UINT2FLOAT(105), UINT2FLOAT(105)};
  [[maybe_unused]] constexpr Color dodgerblue = {UINT2FLOAT(30), UINT2FLOAT(144), UINT2FLOAT(255)};
  [[maybe_unused]] constexpr Color firebrick = {UINT2FLOAT(178), UINT2FLOAT(34), UINT2FLOAT(34)};
  [[maybe_unused]] constexpr Color floralwhite = {UINT2FLOAT(255), UINT2FLOAT(250), UINT2FLOAT(240)};
  [[maybe_unused]] constexpr Color forestgreen = {UINT2FLOAT(34), UINT2FLOAT(139), UINT2FLOAT(34)};
  [[maybe_unused]] constexpr Color fuchsia = {UINT2FLOAT(255), UINT2FLOAT(0), UINT2FLOAT(255)};
  [[maybe_unused]] constexpr Color gainsboro = {UINT2FLOAT(220), UINT2FLOAT(220), UINT2FLOAT(220)};
  [[maybe_unused]] constexpr Color ghostwhite = {UINT2FLOAT(248), UINT2FLOAT(248), UINT2FLOAT(255)};
  [[maybe_unused]] constexpr Color gold = {UINT2FLOAT(255), UINT2FLOAT(215), UINT2FLOAT(0)};
  [[maybe_unused]] constexpr Color goldenrod = {UINT2FLOAT(218), UINT2FLOAT(165), UINT2FLOAT(32)};
  [[maybe_unused]] constexpr Color gray = {UINT2FLOAT(128), UINT2FLOAT(128), UINT2FLOAT(128)};
  [[maybe_unused]] constexpr Color green = {UINT2FLOAT(0), UINT2FLOAT(128), UINT2FLOAT(0)};
  [[maybe_unused]] constexpr Color greenyellow = {UINT2FLOAT(173), UINT2FLOAT(255), UINT2FLOAT(47)};
  [[maybe_unused]] constexpr Color grey = {UINT2FLOAT(128), UINT2FLOAT(128), UINT2FLOAT(128)};
  [[maybe_unused]] constexpr Color honeydew = {UINT2FLOAT(240), UINT2FLOAT(255), UINT2FLOAT(240)};
  [[maybe_unused]] constexpr Color hotpink = {UINT2FLOAT(255), UINT2FLOAT(105), UINT2FLOAT(180)};
  [[maybe_unused]] constexpr Color indianred = {UINT2FLOAT(205), UINT2FLOAT(92), UINT2FLOAT(92)};
  [[maybe_unused]] constexpr Color indigo = {UINT2FLOAT(75), UINT2FLOAT(0), UINT2FLOAT(130)};
  [[maybe_unused]] constexpr Color ivory = {UINT2FLOAT(255), UINT2FLOAT(255), UINT2FLOAT(240)};
  [[maybe_unused]] constexpr Color khaki = {UINT2FLOAT(240), UINT2FLOAT(230), UINT2FLOAT(140)};
  [[maybe_unused]] constexpr Color lavender = {UINT2FLOAT(230), UINT2FLOAT(230), UINT2FLOAT(250)};
  [[maybe_unused]] constexpr Color lavenderblush = {UINT2FLOAT(255), UINT2FLOAT(240), UINT2FLOAT(245)};
  [[maybe_unused]] constexpr Color lawngreen = {UINT2FLOAT(124), UINT2FLOAT(252), UINT2FLOAT(0)};
  [[maybe_unused]] constexpr Color lemonchiffon = {UINT2FLOAT(255), UINT2FLOAT(250), UINT2FLOAT(205)};
  [[maybe_unused]] constexpr Color lightblue = {UINT2FLOAT(173), UINT2FLOAT(216), UINT2FLOAT(230)};
  [[maybe_unused]] constexpr Color lightcoral = {UINT2FLOAT(240), UINT2FLOAT(128), UINT2FLOAT(128)};
  [[maybe_unused]] constexpr Color lightcyan = {UINT2FLOAT(224), UINT2FLOAT(255), UINT2FLOAT(255)};
  [[maybe_unused]] constexpr Color lightgoldenrodyellow = {UINT2FLOAT(250), UINT2FLOAT(250), UINT2FLOAT(210)};
  [[maybe_unused]] constexpr Color lightgray = {UINT2FLOAT(211), UINT2FLOAT(211), UINT2FLOAT(211)};
  [[maybe_unused]] constexpr Color lightgreen = {UINT2FLOAT(144), UINT2FLOAT(238), UINT2FLOAT(144)};
  [[maybe_unused]] constexpr Color lightgrey = {UINT2FLOAT(211), UINT2FLOAT(211), UINT2FLOAT(211)};
  [[maybe_unused]] constexpr Color lightpink = {UINT2FLOAT(255), UINT2FLOAT(182), UINT2FLOAT(193)};
  [[maybe_unused]] constexpr Color lightsalmon = {UINT2FLOAT(255), UINT2FLOAT(160), UINT2FLOAT(122)};
  [[maybe_unused]] constexpr Color lightseagreen = {UINT2FLOAT(32), UINT2FLOAT(178), UINT2FLOAT(170)};
  [[maybe_unused]] constexpr Color lightskyblue = {UINT2FLOAT(135), UINT2FLOAT(206), UINT2FLOAT(250)};
  [[maybe_unused]] constexpr Color lightslategray = {UINT2FLOAT(119), UINT2FLOAT(136), UINT2FLOAT(153)};
  [[maybe_unused]] constexpr Color lightslategrey = {UINT2FLOAT(119), UINT2FLOAT(136), UINT2FLOAT(153)};
  [[maybe_unused]] constexpr Color lightsteelblue = {UINT2FLOAT(176), UINT2FLOAT(196), UINT2FLOAT(222)};
  [[maybe_unused]] constexpr Color lightyellow = {UINT2FLOAT(255), UINT2FLOAT(255), UINT2FLOAT(224)};
  [[maybe_unused]] constexpr Color lime = {UINT2FLOAT(0), UINT2FLOAT(255), UINT2FLOAT(0)};
  [[maybe_unused]] constexpr Color limegreen = {UINT2FLOAT(50), UINT2FLOAT(205), UINT2FLOAT(50)};
  [[maybe_unused]] constexpr Color linen = {UINT2FLOAT(250), UINT2FLOAT(240), UINT2FLOAT(230)};
  [[maybe_unused]] constexpr Color magenta = {UINT2FLOAT(255), UINT2FLOAT(0), UINT2FLOAT(255)};
  [[maybe_unused]] constexpr Color maroon = {UINT2FLOAT(128), UINT2FLOAT(0), UINT2FLOAT(0)};
  [[maybe_unused]] constexpr Color mediumaquamarine = {UINT2FLOAT(102), UINT2FLOAT(205), UINT2FLOAT(170)};
  [[maybe_unused]] constexpr Color mediumblue = {UINT2FLOAT(0), UINT2FLOAT(0), UINT2FLOAT(205)};
  [[maybe_unused]] constexpr Color mediumorchid = {UINT2FLOAT(186), UINT2FLOAT(85), UINT2FLOAT(211)};
  [[maybe_unused]] constexpr Color mediumpurple = {UINT2FLOAT(147), UINT2FLOAT(112), UINT2FLOAT(219)};
  [[maybe_unused]] constexpr Color mediumseagreen = {UINT2FLOAT(60), UINT2FLOAT(179), UINT2FLOAT(113)};
  [[maybe_unused]] constexpr Color mediumslateblue = {UINT2FLOAT(123), UINT2FLOAT(104), UINT2FLOAT(238)};
  [[maybe_unused]] constexpr Color mediumspringgreen = {UINT2FLOAT(0), UINT2FLOAT(250), UINT2FLOAT(154)};
  [[maybe_unused]] constexpr Color mediumturquoise = {UINT2FLOAT(72), UINT2FLOAT(209), UINT2FLOAT(204)};
  [[maybe_unused]] constexpr Color mediumvioletred = {UINT2FLOAT(199), UINT2FLOAT(21), UINT2FLOAT(133)};
  [[maybe_unused]] constexpr Color midnightblue = {UINT2FLOAT(25), UINT2FLOAT(25), UINT2FLOAT(112)};
  [[maybe_unused]] constexpr Color mintcream = {UINT2FLOAT(245), UINT2FLOAT(255), UINT2FLOAT(250)};
  [[maybe_unused]] constexpr Color mistyrose = {UINT2FLOAT(255), UINT2FLOAT(228), UINT2FLOAT(225)};
  [[maybe_unused]] constexpr Color moccasin = {UINT2FLOAT(255), UINT2FLOAT(228), UINT2FLOAT(181)};
  [[maybe_unused]] constexpr Color navajowhite = {UINT2FLOAT(255), UINT2FLOAT(222), UINT2FLOAT(173)};
  [[maybe_unused]] constexpr Color navy = {UINT2FLOAT(0), UINT2FLOAT(0), UINT2FLOAT(128)};
  [[maybe_unused]] constexpr Color oldlace = {UINT2FLOAT(253), UINT2FLOAT(245), UINT2FLOAT(230)};
  [[maybe_unused]] constexpr Color olive = {UINT2FLOAT(128), UINT2FLOAT(128), UINT2FLOAT(0)};
  [[maybe_unused]] constexpr Color olivedrab = {UINT2FLOAT(107), UINT2FLOAT(142), UINT2FLOAT(35)};
  [[maybe_unused]] constexpr Color orange = {UINT2FLOAT(255), UINT2FLOAT(165), UINT2FLOAT(0)};
  [[maybe_unused]] constexpr Color orangered = {UINT2FLOAT(255), UINT2FLOAT(69), UINT2FLOAT(0)};
  [[maybe_unused]] constexpr Color orchid = {UINT2FLOAT(218), UINT2FLOAT(112), UINT2FLOAT(214)};
  [[maybe_unused]] constexpr Color palegoldenrod = {UINT2FLOAT(238), UINT2FLOAT(232), UINT2FLOAT(170)};
  [[maybe_unused]] constexpr Color palegreen = {UINT2FLOAT(152), UINT2FLOAT(251), UINT2FLOAT(152)};
  [[maybe_unused]] constexpr Color paleturquoise = {UINT2FLOAT(175), UINT2FLOAT(238), UINT2FLOAT(238)};
  [[maybe_unused]] constexpr Color palevioletred = {UINT2FLOAT(219), UINT2FLOAT(112), UINT2FLOAT(147)};
  [[maybe_unused]] constexpr Color papayawhip = {UINT2FLOAT(255), UINT2FLOAT(239), UINT2FLOAT(213)};
  [[maybe_unused]] constexpr Color peachpuff = {UINT2FLOAT(255), UINT2FLOAT(218), UINT2FLOAT(185)};
  [[maybe_unused]] constexpr Color peru = {UINT2FLOAT(205), UINT2FLOAT(133), UINT2FLOAT(63)};
  [[maybe_unused]] constexpr Color pink = {UINT2FLOAT(255), UINT2FLOAT(192), UINT2FLOAT(203)};
  [[maybe_unused]] constexpr Color plum = {UINT2FLOAT(221), UINT2FLOAT(160), UINT2FLOAT(221)};
  [[maybe_unused]] constexpr Color powderblue = {UINT2FLOAT(176), UINT2FLOAT(224), UINT2FLOAT(230)};
  [[maybe_unused]] constexpr Color purple = {UINT2FLOAT(128), UINT2FLOAT(0), UINT2FLOAT(128)};
  [[maybe_unused]] constexpr Color red = {UINT2FLOAT(255), UINT2FLOAT(0), UINT2FLOAT(0)};
  [[maybe_unused]] constexpr Color rosybrown = {UINT2FLOAT(188), UINT2FLOAT(143), UINT2FLOAT(143)};
  [[maybe_unused]] constexpr Color royalblue = {UINT2FLOAT(65), UINT2FLOAT(105), UINT2FLOAT(225)};
  [[maybe_unused]] constexpr Color saddlebrown = {UINT2FLOAT(139), UINT2FLOAT(69), UINT2FLOAT(19)};
  [[maybe_unused]] constexpr Color salmon = {UINT2FLOAT(250), UINT2FLOAT(128), UINT2FLOAT(114)};
  [[maybe_unused]] constexpr Color sandybrown = {UINT2FLOAT(244), UINT2FLOAT(164), UINT2FLOAT(96)};
  [[maybe_unused]] constexpr Color seagreen = {UINT2FLOAT(46), UINT2FLOAT(139), UINT2FLOAT(87)};
  [[maybe_unused]] constexpr Color seashell = {UINT2FLOAT(255), UINT2FLOAT(245), UINT2FLOAT(238)};
  [[maybe_unused]] constexpr Color sienna = {UINT2FLOAT(160), UINT2FLOAT(82), UINT2FLOAT(45)};
  [[maybe_unused]] constexpr Color silver = {UINT2FLOAT(192), UINT2FLOAT(192), UINT2FLOAT(192)};
  [[maybe_unused]] constexpr Color skyblue = {UINT2FLOAT(135), UINT2FLOAT(206), UINT2FLOAT(235)};
  [[maybe_unused]] constexpr Color slateblue = {UINT2FLOAT(106), UINT2FLOAT(90), UINT2FLOAT(205)};
  [[maybe_unused]] constexpr Color slategray = {UINT2FLOAT(112), UINT2FLOAT(128), UINT2FLOAT(144)};
  [[maybe_unused]] constexpr Color slategrey = {UINT2FLOAT(112), UINT2FLOAT(128), UINT2FLOAT(144)};
  [[maybe_unused]] constexpr Color snow = {UINT2FLOAT(255), UINT2FLOAT(250), UINT2FLOAT(250)};
  [[maybe_unused]] constexpr Color springgreen = {UINT2FLOAT(0), UINT2FLOAT(255), UINT2FLOAT(127)};
  [[maybe_unused]] constexpr Color steelblue = {UINT2FLOAT(70), UINT2FLOAT(130), UINT2FLOAT(180)};
  [[maybe_unused]] constexpr Color tan = {UINT2FLOAT(210), UINT2FLOAT(180), UINT2FLOAT(140)};
  [[maybe_unused]] constexpr Color teal = {UINT2FLOAT(0), UINT2FLOAT(128), UINT2FLOAT(128)};
  [[maybe_unused]] constexpr Color thistle = {UINT2FLOAT(216), UINT2FLOAT(191), UINT2FLOAT(216)};
  [[maybe_unused]] constexpr Color tomato = {UINT2FLOAT(255), UINT2FLOAT(99), UINT2FLOAT(71)};
  [[maybe_unused]] constexpr Color turquoise = {UINT2FLOAT(64), UINT2FLOAT(224), UINT2FLOAT(208)};
  [[maybe_unused]] constexpr Color violet = {UINT2FLOAT(238), UINT2FLOAT(130), UINT2FLOAT(238)};
  [[maybe_unused]] constexpr Color wheat = {UINT2FLOAT(245), UINT2FLOAT(222), UINT2FLOAT(179)};
  [[maybe_unused]] constexpr Color white = {UINT2FLOAT(255), UINT2FLOAT(255), UINT2FLOAT(255)};
  [[maybe_unused]] constexpr Color whitesmoke = {UINT2FLOAT(245), UINT2FLOAT(245), UINT2FLOAT(245)};
  [[maybe_unused]] constexpr Color yellow = {UINT2FLOAT(255), UINT2FLOAT(255), UINT2FLOAT(0)};
  [[maybe_unused]] constexpr Color yellowgreen = {UINT2FLOAT(154), UINT2FLOAT(205), UINT2FLOAT(50)};

#undef UINT2FLOAT


}// namespace engine::graphics::color