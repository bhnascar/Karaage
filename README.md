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
3. Select/Deselect multiple cubes
4. Delete cube
5. Display local orientation (axes) of cube
6. Rotate (Local X/Y/Z)
7. Translate (World X/Y/Z)
8. Scale (Local X/Y/Z)
9. 3D cursor (Moves left/right/forward/backward/up/down)

Editor actions are currently triggered by a combination of mouse actions and keyboard shortcuts. We are looking into adding alternative input by having other input devices simply fire off the corresponding keyboard and mouse events. Eventually we will want more native integration, but this may be adequate for the purposes of prototyping.

### Goals
1. Recreate minimal editor functionality (enough for simple level design)
2. Integrate 3DConnexion Space Navigator support to test level design workflow with said device
3. Integrate Novint Falcon support and test level design workflow
4. Integrate mobile device object-manipulation support and test level design workflow

## Karaage.io

This is the landing page for the Karaage level editor that also details editor progress over time. Note that `secrets.yml` is in the `.gitignore` - please generate your own secrets in order to run your own copy of the website.

### Setup

karaage.io is built on Ruby on Rails and developed with Ruby 2.1.0. Please check that your environment is setup as such, and run `bundle install` to make sure everything is up to date.

### Updating the site

Whenever you update or add CSS, JavaScript, or other media, be sure to run `rake assets:precompile` to make sure all assets are compressed for speed.
