var contentTypes = ['boxes', 'cylinders', 'cones', 'spheres', 'wedges'];
var contentIcons = ['hud_icons/Cube.png', 'hud_icons/Cylinder.png', 'hud_icons/Cone.png', 'hud_icons/Sphere.png', 'hud_icons/Wedge.png']
var transformTypes = ['translate', 'scale', 'rotate'];
var transformIcons = ['hud_icons/Translate.png', 'hud_icons/Scale.png', 'hud_icons/Rotate.png'];

var originalCSS = {
  width: "100%",
  marginTop: "35%",
  paddingLeft: "35%",
  paddingRight: "35%"
};
var miniCSS = {
  width: "50%",
  marginTop: "65%",
  paddingLeft: "5%",
  paddingRight: "5%"
};

$('.menu-container').delay(1000).animate(miniCSS);

engine.on('SetContentTypeForHud', function (index) {
  if ($('.menu-container').is(':animated')) {
    $('.menu-container').stop();
  }
  $('#mode-content').html('Inserting ' + contentTypes[index]);
  $('#mode-icon').attr('src', contentIcons[index]);
  $('.menu-container').animate(originalCSS, 500, function () {
    $('.menu-container').delay(1500).animate(miniCSS);
  })
});

engine.on('SetTransformationTypeForHud', function (index) {
  if ($('.menu-container').is(':animated')) {
    $('.menu-container').stop();
  }
  $('#mode-content').html('Transformation: ' + transformTypes[index]);
  $('#mode-icon').attr('src', transformIcons[index]);
  $('.menu-container').animate(originalCSS, 500, function () {
    $('.menu-container').delay(1500).animate(miniCSS);
  });
});

// Testing
// var testIndex = 0;
// setInterval(function() {
//   testIndex++;
//   if ($('.menu-container').is(':animated')) {
//     $('.menu-container').stop();
//   }
//   $('#mode-content').html('Transformation: ' + transformTypes[testIndex % 3]);
//   $('#mode-icon').attr('src', transformIcons[testIndex % 3]);
//   $('.menu-container').animate(originalCSS, 500, function () {
//     $('.menu-container').delay(1500).animate(miniCSS);
//   });
// }, 5000);