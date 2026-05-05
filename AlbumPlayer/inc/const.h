#ifndef CONST_H
#define CONST_H

enum TreeItemType{
    TreeItemProj = 1,
    TreeItemDir = 2,
    TreeItemPic = 3
};

enum PicBtnState{
    PicBtnStateNormal = 1,  //“播放按钮状态”
    PicBtnStateHover = 2,
    PicBtnStatePressed = 3,

    PicBtnState2Normal = 4, //“停止按钮状态”
    PicBtnState2Hover = 5,
    PicBtnState2Pressed = 6
};

enum MyMediaPlayerlistMode{
    CurrentItemOnce = 1,
    CurrentItemInLoop,
    Sequential,
    Loop,
    Random
};

enum MyMediaStopState{
    PrevBtn = -1,
    NormalEnd = 0,
    NextBtn = 1
};

const int PROGRESS_WIDTH = 300;
const int PROGRESS_MAX = 300;
const int ABBRITEM_SIZE = 100;
const int ABBRICON_SIZE = 90;

const int MAX_ABBRPAGEICONS = 17;

#endif // CONST_H


