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

engine.on('3DMouseRotateX', function (argument) {
  var menuCount = $(".list-group-item:visible").length;

  var activeItem = $(".active");
  var activeIndex = activeItem.parent().children().index(activeItem);

  if (argument >= 0) {
    activeIndex = (activeIndex + 1) % menuCount;
  }
  else {
    activeIndex = (activeIndex - 1 + menuCount) % menuCount;
  }
  $(".list-group-item").removeClass('active');
  $(".list-group-item:visible").eq(activeIndex).addClass('active');
});


// Keyboard shortcuts for testing
$(document).keydown(function(e) {
    switch(e.which) {
        case 13: { // enter
          $(".active").click();
          break;
        }

        case 37:  {// left
          break;
        }

        case 38: // up
          var menuCount = $(".list-group-item:visible").length;

          var activeItem = $(".active");
          var activeIndex = activeItem.parent().children().index(activeItem);

          activeIndex = (activeIndex - 1 + menuCount) % menuCount;

          $(".list-group-item").removeClass('active');
          $(".list-group-item:visible").eq(activeIndex).addClass('active');
        break;

        case 39: { // right
          break;
        }

        case 40: // down
          var menuCount = $(".list-group-item:visible").length;

          var activeItem = $(".active");
          var activeIndex = activeItem.parent().children().index(activeItem);

          activeIndex = (activeIndex + 1) % menuCount;

          $(".list-group-item").removeClass('active');
          $(".list-group-item:visible").eq(activeIndex).addClass('active');
        break;

        default: return; // exit this handler for other keys
    }
    e.preventDefault(); // prevent the default action (scroll / move caret)
});