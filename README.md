# Karaage
Prototype level editor built as a game level using Unreal Engine 4. Please check out our project home site at www.karaage.io.

![alt tag](https://github.com/cs210/Karaage/blob/master/editor.png)

## Current supported functionality
1. Add cube
2. Select/Deselect cube
3. Select/Deselect multiple cubes
4. Delete cube
5. Display local orientation (axes) of cube
6. Rotate (Local X/Y/Z)
7. Translate (World X/Y/Z)
8. Scale (Local X/Y/Z)
9. 3D cursor (Moves left/right/forward/backwards)

Editor actions are currently triggered by a combination of mouse actions and keyboard shortcuts. We are looking into adding alternative input by having other input devices simply fire off the corresponding keyboard and mouse events. Eventually we will want more native integration, but this may be adequate for the purposes of prototyping.

## Goals
1. Recreate minimal editor functionality (enough for simple level design)
2. Integrate 3DConnexion Space Navigator support to test level design workflow with said device
3. Integrate Novint Falcon support and test level design workflow
4. Integrate mobile device object-manipulation support and test level design workflow
