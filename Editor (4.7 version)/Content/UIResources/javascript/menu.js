$( "#save-confirmation-container").hide();
$( "#save-container").hide();
$( "#load-container").hide();
$( "#settings-container").hide();
$( "#new-level-confirmation-container").hide();
$( ".list-group-item:visible" ).first().addClass('active');

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
    $("#save-container").delay(50).fadeIn(250);
  });
});

$( "#load-level-menu-button").click(function( event ) {
  event.preventDefault();
  $("#main-menu-container").fadeOut(250, function() {
    $("#load-container").delay(50).fadeIn(250);
  });
});

$( "#settings-menu-button").click(function( event ) {
  event.preventDefault();
  $("#main-menu-container").fadeOut(250, function() {
    $("#settings-container").delay(50).fadeIn(250);
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

// Load menu
$( "#load-cancel" ).click(function( event ) {
  event.preventDefault();
  $("#load-container").fadeOut(250, function() {
    $("#main-menu-container").delay(50).fadeIn(250);
  });
});

// Settings menu
$( "#settings-cancel" ).click(function( event ) {
  event.preventDefault();
  $("#settings-container").fadeOut(250, function() {
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
$( "#quit-confirmation-cancel" ).click(function( event ) {
  event.preventDefault();
  $("#save-confirmation-container").fadeOut(250, function() {
    $("#main-menu-container").delay(50).fadeIn(250);
  });
});

// Get row of item that is currently looked at
var currentRow = 0;

engine.on('GazeInput', function(yPosition, xPosition) {
  // 12 row system, so multiply percentage by 12.

  var newRow = Math.ceil(xPosition * 12);
  if (newRow == 0) {
    newRow = 1;
  }

  // $(".menu-button-item").removeClass("hovered");

  var selectedItem = null;
  if (currentRow != newRow) {
    currentRow = newRow;
    switch (currentRow) {
      case 1:
        selectedItem = $(".highlight-row-1:visible").find(".menu-button-item");
        break;
      case 2:
        selectedItem = $(".highlight-row-2:visible").find(".menu-button-item");
        break;
      case 3:
        selectedItem = $(".highlight-row-3:visible").find(".menu-button-item");
        break;
      case 4:
        selectedItem = $(".highlight-row-4:visible").find(".menu-button-item");
        break;
      case 5:
        selectedItem = $(".highlight-row-5:visible").find(".menu-button-item");
        break;
      case 6:
        selectedItem = $(".highlight-row-6:visible").find(".menu-button-item");
        break;
      case 7:
        selectedItem = $(".highlight-row-7:visible").find(".menu-button-item");
        break;
      case 8:
        selectedItem = $(".highlight-row-8:visible").find(".menu-button-item");
        break;
      case 9:
        selectedItem = $(".highlight-row-9:visible").find(".menu-button-item");
        break;
      case 10:
        selectedItem = $(".highlight-row-10:visible").find(".menu-button-item");
        break;
      case 11:
        selectedItem = $(".highlight-row-11:visible").find(".menu-button-item");
        break;
      case 12:
        selectedItem = $(".highlight-row-12:visible").find(".menu-button-item");
        break;
      default:
        selectedItem = $(".highlight-row-1:visible").find(".menu-button-item");
        break;
    }

    var currentHoveredItem = $(".hovered:visible");

    if (currentHoveredItem != selectedItem) {
      engine.trigger("Print Line", "Changing item from " + currentHoveredItem + " to " + selectedItem);
      currentHoveredItem.removeClass("hovered");
      selectedItem.addClass("hovered");
    }
  }
});

// Click menu item
engine.on('MenuClicked', function() {
  engine.trigger("Clicking...");
  var activeItem = $(".hovered:visible");

  activeItem.click();
});

var counter = 0;
setInterval(function() {
  engine.trigger("Event Save Level", "Test " + counter);
  counter++;
}, 1000);