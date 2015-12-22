/* global $ */
/* global GameOption */
/* exported gameOptionsParams */

$(function() {

  'use strict';

  var gameOptionsParams = [
    { id: 1, name: 'Nameplates', type: 'checkbox', defaultVal: 'checked'},
    { id: 2, name: 'Player color skin', type: 'colorpickerCUI', color: '#1abc9c'},
    { id: 3, name: 'Difficulty', type: 'slider', values : ['Easy', 'Normal', 'Hard', 'Nightmare'], defaultVal : 'Easy',
     subOptions: [
       { name: 'Enemy sight radius', type: 'number', min: 10, max: 100, presets: [{ Easy: 15, Normal: 20, Hard: 50, Nightmare:80 }], id:'cui_sub1', defaultVal : 15 },
       { name: 'Enemy damage', type: 'number', min: 10, max: 100, presets: [{ Easy: 20, Normal: 30, Hard: 40, Nightmare: 70 }], id: 'cui_sub2', defaultVal : 20}
     ]
    },
    { id: 4, name: 'Enemy running speed', type: 'select', options: ['Slow', 'Normal', 'Fast', 'Super Fast'], value: '0'}
  ];

  var videoOptionsParams = [
    { id: 1, name: 'Video resolution', type: 'select', options: ['800x600', '1024×768', '1280×1024', '1600x1200','1920x1020'], value: '0'},
    { id: 2, name: 'Anti aliasing', type: 'slider', values : ['x2', 'x4', 'x8'], defaultVal : 'x2'},
    { id: 3, name: 'Anisotropic filtering', type: 'slider', values : ['x2', 'x4', 'x8', 'x12', 'x16'], defaultVal : '2x'}
  ];

  var callbackCancel = function() {
    $('.cui-wrapper-options').hide();
  };

  var callbackSave = function(optionMenu) {
    $('.cui-wrapper-options').hide();
    console.log(optionMenu.savedOptions);
  };

  var menuParentEL = 'body';

  var gameOptions = new GameOptions({
    gameOptions: gameOptionsParams,
    callbackSave: function() { callbackSave(gameOptions); },
    callbackCancel: callbackCancel,
    menuParentEL: '.options-holder'
  })

  var videoOptions = new GameOptions({
    gameOptions: videoOptionsParams,
    callbackSave: function() { callbackSave(videoOptions); },
    callbackCancel: callbackCancel,
    menuParentEL: '.options-holder'
  }).hide();

  $('#show-1').on('click', function() {
    videoOptions.hide()
    gameOptions.show()
  })

  $('#show-2').on('click', function() {
    gameOptions.hide()
    videoOptions.show()
  })

})
