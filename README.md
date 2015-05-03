# Karaage
Prototype level editor built as a game level using Unreal Engine 4. Please check out our project home site at www.karaage.io.

![alt tag](https://github.com/cs210/Karaage/blob/master/editor.png)

## Karaage Editor

### Current supported functionality
1. Add cube
  1. By player position
  2. By cursor position
  3. By trigger point
2. Select/Deselect cube
  1. By line trace from player viewpoint
  2. By line trace through cursor
  3. By cursor overlap
3. ~~Select/Deselect multiple cubes~~
4. Delete cube
5. Display local orientation (axes) of cube
6. Rotate (Local X/Y/Z) (via keyboard - Falcon control scheme in in the works)
7. Translate (World X/Y/Z) (with Falcon)
8. Scale (Local X/Y/Z) (with Falcon)
9. Drop-to-ground
10. 3D cursor (Moves left/right/forward/backward/up/down)
11. Highlight when cursor overlaps object
12. Multiple types of objects (cube/sphere/cone/wedge/cylinder)
13. Snapping to nearest grid ticks in all axes
14. 3D mouse support (functional, but code needs refinement) (now with analog input!)
15. Novint Falcon support

### Stretch features
1. Multiple select (by dragging a bounding volume)
2. Add new object by dragging and cloning

### Goals
1. ~~Recreate minimal editor functionality (enough for simple level design)~~
2. ~~Integrate 3DConnexion Space Navigator support to test level design workflow with said device~~
3. ~~Integrate Novint Falcon support and test level design workflow~~
4. ~~Integrate mobile device object-manipulation support and test level design workflow~~
5. Create functional menu for editor settings
6. Export created levels to UE4
7. Haptic feedback for Novint Falcon. Ex: Magnetic lines to guide axis-specific edits, haptic walls to guide precise object placement.

## Running the editor
The Karaage editor requires a 3DConnexion Space Navigator and Novint Falcon. If you don't have these devices already, you can buy a Space Navigator at the [3DConnexion store](http://www.3dconnexion.com/buy/shop.html) and a Falcon at the [Novint store](https://www.novint.com/index.php/store).

Please install the following drivers BEFORE plugging in the devices to avoid any issues with the plug-and-play system installing the wrong drivers. The drivers for the Space Navigator can be found [online here](http://www.3dconnexion.com/service/drivers.html). The drivers for the Novint Falcon can be found [at the bottom of the page here](http://web.stanford.edu/class/cs277/assignments/index.html). 

Note that we are NOT using the official Novint Falcon drivers! This is because we want to work with Chai3D 3.0 (see below).

## Build guide (read carefully!)
Building the Karaage UE4 project from the source requires libraries for 3DConnexion and Chai3D / Novint Falcon, which we have included along with our Connexion and Chai3D plugins. Additionally, you will need to install the third-party CoherentUI plugin.

### 3DConnexion
The Connexion plugin should be installed to the Unreal source as an engine plugin at Engine/Plugins/Developer. The supporting library should be installed at Engine/Source/ThirdParty/connexion. The supporting library includes headers and precompiled versions of the 3DConnexion library for x86 and x64 Windows machines. Should you need to recompile these libraries from the source, you can download the SDK from the [3DConnexion website here](http://www.3dconnexion.com/service/software-developer.html), but you will have to sign up with a developer account and wait for your request to be approved.

### Chai3D / Novint Falcon
The Chai3D plugin should be installed to the Unreal source as an engine plugin at Engine/Plugins/Developer. The supporting library should be installed at Engine/Source/ThirdParty/chai3d. This supporting library includes headers and precompiled versions of the Chai3D haptics library for x86 and x64 Windows machines. Should you need to recompile the Chai3D from the source, you can [find it online here](http://web.stanford.edu/class/cs277/assignments/index.html). 

Don't download Chai3D from the official site! The official release is at 2.0 and is dated; it hasn't been updated for some time and version 3.0 has a lot of new features. We chose to use Chai3D 3.0 because we used it in a haptics class at Stanford before, and we wanted to stick to something that we knew would work for sure. (The class was actually taught by Ken Salisbury, Sonny Chan, and Francois Conti, who are leading researchers in haptics and contributors to the Chai3D project).

### CoherentUI
The Karaage UE4 project requires the CoherentUI engine plugin to load. You can download a trial version of the Coherent [here](https://coherent-labs.com/ue4/), but again, you will have to sign up with a developer account and wait for your request to be approved. Note that CoherentUI currently supports UE4 up to version 4.7. This means it does not work with the promoted UE4 branch!

## Karaage.io

This is the landing page for the Karaage level editor that also details editor progress over time. Note that `secrets.yml` is in the `.gitignore` - please generate your own secrets in order to run your own copy of the website.

### Setup

karaage.io is built on Ruby on Rails and developed with Ruby 2.1.0. Please check that your environment is setup as such, and run `bundle install` to make sure everything is up to date.

### Updating the site

Whenever you update or add CSS, JavaScript, or other media, be sure to run `rake assets:precompile` to make sure all assets are compressed for speed.
