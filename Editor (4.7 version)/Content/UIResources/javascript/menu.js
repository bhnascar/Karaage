$( "#save-confirmation-container").hide();
$( "#new-level-confirmation-container").hide();

$( "#new-level-menu-button" ).click(function( event ) {
  event.preventDefault();
  $("#main-menu-container").fadeOut(250, function() {
    $("#new-level-confirmation-container").delay(50).fadeIn(250);
  });
});

$( "#quit-menu-button" ).click(function( event ) {
  event.preventDefault();
  $("#main-menu-container").fadeOut(250, function() {
    $("#save-confirmation-container").delay(50).fadeIn(250);
  });
});

// New level confirmation menu
$( "#new-level-confirmation-cancel" ).click(function( event ) {
  event.preventDefault();
  $("#new-level-confirmation-container").fadeOut(250, function() {
    $("#main-menu-container").delay(50).fadeIn(250);
  });
});

// Save confirmation menu
$( "#save-confirmation-cancel" ).click(function( event ) {
  event.preventDefault();
  $("#save-confirmation-container").fadeOut(250, function() {
    $("#main-menu-container").delay(50).fadeIn(250);
  });
});