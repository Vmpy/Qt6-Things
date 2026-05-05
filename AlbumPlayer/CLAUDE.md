# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project overview

An electronic photo album (电子相册) desktop app built with Qt6 (C++17). It browses image collections in a project/directory tree, plays background music (mp3/wav), and runs slideshows with crossfade animations.

## Directory structure

```
AlbumPlayer/
├── AlbumPlayer.pro          # qmake project file
├── rc.qrc                   # Qt resource file (icons, stylesheet)
├── src/                     # C++ source files (.cpp)
├── inc/                     # C++ header files (.h)
├── layout/                  # Qt Designer UI files (.ui)
├── icon/                    # Icons (SVG, PNG, ICO)
├── style/                   # QSS stylesheet
├── requirement/             # Feature requirement docs (Chinese)
└── release/                 # Build output (qmake Release)
```

Headers are included by bare filename (e.g. `#include "picshow.h"`) — `AlbumPlayer.pro` adds `INCLUDEPATH += $$PWD/inc`.

## Build & run

```bash
# Configure (once)
qmake AlbumPlayer.pro
make

# Or open in Qt Creator: AlbumPlayer.pro → configure with Qt 6.11.0 MinGW 64-bit
```

The build output goes to `build/Desktop_Qt_6_11_0_MinGW_64_bit-Debug/`.

There is also a CMake project (see recent commit `8df246f`), but the primary build system is qmake.

## Architecture

The app has two main zones, laid out horizontally in `MainWindow`:

**Left zone — Project tree** (`ProjTree` → `ProjTreeWidget`, a custom QTreeWidget)
- Each project is a root node; child nodes are directories and image files.
- Right-click context menu: import images, set as active project, slide show, close project.
- `ProjTreeThread` copies files into the project directory while building the tree. `OpenTreeThread` re-opens an existing project from disk.
- `ProjTreeItem` has prev/next sibling pointers forming a doubly-linked chain for photo navigation.

**Right zone — Image display** (`PicShow`, a QDialog)
- Shows the currently selected image. Prev/next buttons appear on mouse hover.
- Emits `sigPrevBtnClicked`/`sigNextBtnClicked` which `ProjTreeWidget` handles by walking the linked item chain.

**Toolbar — Music controls**
- `MyMediaPlayer` wraps `QMediaPlayer` + `QAudioOutput`. Manages playlist, 5 play modes (`const.h:MyMediaPlayerlistMode`), volume, and a master on/off switch.
- Playback controls (play, pause, stop, prev, next, play mode toggle) live in the left toolbar.
- Status bar labels show current track, play mode, play state, and playlist size.

**Slideshow** (`SlideShowDialog`)
- Full-screen dialog with `PicAnimationWidget` (crossfade between two QPixmaps via QTimer), prev/next buttons, and an `AbbrListWidget` horizontal thumbnail strip.

**Custom widgets**
- `PicButton` — QPushButton with separate normal/hover/pressed icons.
- `PicStateButton` — QPushButton with two icon sets for toggle behavior (e.g. play ↔ pause).
- `PicAnimationWidget` — crossfade slideshow using `_factor` opacity interpolation.

**Wizard** — `Wizard` (QWizard) collects project name + path for creation. Emits `sigProjSetting` to `ProjTree::slotAddProjToTree`.

## Key data flow

```
Wizard::sigProjSetting → ProjTree::slotAddProjToTree → ProjTreeWidget::AddProjToTree
MainWindow::sigOpenProj → ProjTreeWidget::slotOpenProj
ProjTreeWidget::sigUpdateSelected → PicShow::slotSelectedItem
PicShow::sigPrevBtnClicked / sigNextBtnClicked → ProjTreeWidget::slotPrevBtnClicked / slotNextBtnClicked
ProjTreeWidget::sigClearSelected → PicShow::slotClearSelected
```

## Styling

Dark theme defined in `style/style.qss`, loaded from Qt resources (`rc.qrc`) in `main.cpp` via `QApplication::setStyleSheet()`.
