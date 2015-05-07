var contentTypes = ['boxes', 'cylinders', 'cones', 'spheres', 'wedges'];
var transformTypes = ['translate', 'scale', 'rotate'];

$('.menu-container').fadeOut(3000);

engine.on('SetContentTypeForHud', function (index) {
  if ($('.menu-container').is(':animated')) {
    $('.menu-container').stop().animate({opacity:'100'});
  }
  $('.menu-container').show();
  $('#mode-content').html('Inserting' + contentTypes[index]);
  $('.menu-container').fadeOut(3000);
});

engine.on('SetTransformationTypeForHud', function (index) {
  if ($('.menu-container').is(':animated')) {
    $('.menu-container').stop().animate({opacity:'100'});
  }
  $('.menu-container').show();
  $('#mode-content').html('Transformation: ' + transformTypes[index]);
  $('.menu-container').fadeOut(3000);
});