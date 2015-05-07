var contentTypes = ['boxes', 'cylinders', 'cones', 'spheres', 'wedges'];

engine.on(SetContentTypeForHud, function (index) {
  $("#content-type").html(contentTypes[index]);
});