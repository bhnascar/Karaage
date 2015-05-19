$( "#save-confirmation-container").hide();
$( "#save-container").hide();
$( "#new-level-confirmation-container").hide();
$( ".list-group-item:visible" ).first().addClass('active');

// Main menu
$( "#new-level-menu-button" ).click(function( event ) {
  event.preventDefault();
  $("#main-menu-container").fadeOut(250, function() {
    $(".list-group-item").removeClass('active');
    $("#new-level-confirmation-container").delay(50).fadeIn(250, function() {
      $(".list-group-item:visible").first().addClass('active');
    });
  });
});

$( "#save-level-menu-button").click(function( event ) {
  event.preventDefault();
  $("#main-menu-container").fadeOut(250, function() {
    $(".list-group-item").removeClass('active');
    $("#save-container").delay(50).fadeIn(250, function () {
      $("#file-name-input").focus();
      $(".list-group-item:visible").first().addClass('active');
    });
  });
});

$( "#quit-menu-button" ).click(function( event ) {
  event.preventDefault();
  $("#main-menu-container").fadeOut(250, function() {
    $(".list-group-item").removeClass('active');
    $("#save-confirmation-container").delay(50).fadeIn(250, function() {
      $(".list-group-item:visible").first().addClass('active');
    });
  });
});

// Save as menu
$( "#save-cancel" ).click(function( event ) {
  event.preventDefault();
  $("#save-container").fadeOut(250, function() {
    $(".list-group-item").removeClass('active');
    $("#main-menu-container").delay(50).fadeIn(250, function() {
      $("#file-name-input").val("");
      $(".list-group-item:visible").first().addClass('active');
    });
  });
});

// New level confirmation menu
$( "#new-level-confirmation-cancel" ).click(function( event ) {
  event.preventDefault();
  $("#new-level-confirmation-container").fadeOut(250, function() {
    $(".list-group-item").removeClass('active');
    $("#main-menu-container").delay(50).fadeIn(250, function() {
      $(".list-group-item:visible").first().addClass('active');
    });
  });
});

// Quit confirmation menu
$( "#save-confirmation-cancel" ).click(function( event ) {
  event.preventDefault();
  $("#save-confirmation-container").fadeOut(250, function() {
    $(".list-group-item").removeClass('active');
    $("#main-menu-container").delay(50).fadeIn(250, function() {
      $(".list-group-item:visible").first().addClass('active');
    });
  });
});

engine.on('3DMouseRotateX', function (index) {
  var menuCount = $(".list-group-item:visible").length;
});
