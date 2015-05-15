$( "#save-confirmation-container").hide();
$( "#save-container").hide();
$( "#new-level-confirmation-container").hide();

// Main menu
$( "#new-level-menu-button" ).click(function( event ) {
  event.preventDefault();
  $("#main-menu-container").fadeOut(250, function() {
    $("#new-level-confirmation-container").delay(50).fadeIn(250);
  });
});

$( "#save-level-menu-button").click(function( event ) {
  event.preventDefault();
  $("#main-menu-container").fadeOut(250, function() {
    $("#save-container").delay(50).fadeIn(250, function () {
      $("#file-name-input").focus();
    });
  });
});

$( "#quit-menu-button" ).click(function( event ) {
  event.preventDefault();
  $("#main-menu-container").fadeOut(250, function() {
    $("#save-confirmation-container").delay(50).fadeIn(250);
  });
});

// Save as menu
$( "#save-cancel" ).click(function( event ) {
  event.preventDefault();
  $("#save-container").fadeOut(250, function() {
    $("#main-menu-container").delay(50).fadeIn(250);
  });
});

// New level confirmation menu
$( "#new-level-confirmation-cancel" ).click(function( event ) {
  event.preventDefault();
  $("#new-level-confirmation-container").fadeOut(250, function() {
    $("#main-menu-container").delay(50).fadeIn(250);
  });
});

// Quit confirmation menu
$( "#save-confirmation-cancel" ).click(function( event ) {
  event.preventDefault();
  $("#save-confirmation-container").fadeOut(250, function() {
    $("#main-menu-container").delay(50).fadeIn(250);
  });
});