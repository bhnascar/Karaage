$( "#save-confirmation-container").hide();
$( "#save-container").hide();
$( "#load-container").hide();
$( "#settings-container").hide();
$( "#new-level-confirmation-container").hide();
$( "#load-complete-container" ).hide();
$( "#main-menu-container").hide();

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
    engine.trigger("Event Get Save Slot Metadata", "level1");
    engine.trigger("Event Get Save Slot Metadata", "level2");
    engine.trigger("Event Get Save Slot Metadata", "level3");
    engine.trigger("Event Get Save Slot Metadata", "level4");
    engine.trigger("Event Get Save Slot Metadata", "level5");
    engine.trigger("Event Get Save Slot Metadata", "level6");
    engine.trigger("Event Get Save Slot Metadata", "level7");
    engine.trigger("Event Get Save Slot Metadata", "level8");
    engine.trigger("Event Get Save Slot Metadata", "level9");
    engine.trigger("Event Get Save Slot Metadata", "level10");
    $("#save-container").delay(50).fadeIn(250);
  });
});

$( "#load-level-menu-button").click(function( event ) {
  event.preventDefault();
  $("#main-menu-container").fadeOut(250, function() {
    engine.trigger("Event Get Save Slot Metadata", "level1");
    engine.trigger("Event Get Save Slot Metadata", "level2");
    engine.trigger("Event Get Save Slot Metadata", "level3");
    engine.trigger("Event Get Save Slot Metadata", "level4");
    engine.trigger("Event Get Save Slot Metadata", "level5");
    engine.trigger("Event Get Save Slot Metadata", "level6");
    engine.trigger("Event Get Save Slot Metadata", "level7");
    engine.trigger("Event Get Save Slot Metadata", "level8");
    engine.trigger("Event Get Save Slot Metadata", "level9");
    engine.trigger("Event Get Save Slot Metadata", "level10");
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
var saveFunction = function (index) {
  var currentDate = new Date(); 
  var modifiedDate = "Modified: " + currentDate.getDate() + "/"
                  + (currentDate.getMonth()+1)  + "/" 
                  + currentDate.getFullYear() + " @ "  
                  + currentDate.getHours() + ":"  
                  + currentDate.getMinutes();

  engine.trigger("Print Line", modifiedDate + " | level" + index)
  engine.trigger("Event Save Level", "level" + index, modifiedDate);
};

$( "#save-level-1").click(function ( event ) {
  event.preventDefault();
  saveFunction(1);
});
$( "#save-level-2").click(function ( event ) {
  event.preventDefault();
  saveFunction(2);
});
$( "#save-level-3").click(function ( event ) {
  event.preventDefault();
  saveFunction(3);
});
$( "#save-level-4").click(function ( event ) {
  event.preventDefault();
  saveFunction(4);
});
$( "#save-level-5").click(function ( event ) {
  event.preventDefault();
  saveFunction(5);
});
$( "#save-level-6").click(function ( event ) {
  event.preventDefault();
  saveFunction(6);
});
$( "#save-level-7").click(function ( event ) {
  event.preventDefault();
  saveFunction(7);
});
$( "#save-level-8").click(function ( event ) {
  event.preventDefault();
  saveFunction(8);
});
$( "#save-level-9").click(function ( event ) {
  event.preventDefault();
  saveFunction(9);
});
$( "#save-level-10").click(function ( event ) {
  event.preventDefault();
  saveFunction(10);
});

$( "#save-cancel" ).click(function( event ) {
  event.preventDefault();
  $("#save-container").fadeOut(250, function() {
    $("#main-menu-container").delay(50).fadeIn(250);
  });
});

// Load menu
var loadFunction = function (index) {
  engine.trigger("Event Load Level", "level" + index);
};

$( "#load-level-1").click(function ( event ) {
  event.preventDefault();
  loadFunction(1);
});
$( "#load-level-2").click(function ( event ) {
  event.preventDefault();
  loadFunction(2);
});
$( "#load-level-3").click(function ( event ) {
  event.preventDefault();
  loadFunction(3);
});
$( "#load-level-4").click(function ( event ) {
  event.preventDefault();
  loadFunction(4);
});
$( "#load-level-5").click(function ( event ) {
  event.preventDefault();
  loadFunction(5);
});
$( "#load-level-6").click(function ( event ) {
  event.preventDefault();
  loadFunction(6);
});
$( "#load-level-7").click(function ( event ) {
  event.preventDefault();
  loadFunction(7);
});
$( "#load-level-8").click(function ( event ) {
  event.preventDefault();
  loadFunction(8);
});
$( "#load-level-9").click(function ( event ) {
  event.preventDefault();
  loadFunction(9);
});
$( "#load-level-10").click(function ( event ) {
  event.preventDefault();
  loadFunction(10);
});
$( "#load-level-default").click(function ( event ) {
  event.preventDefault();
  loadFunction(100);
});

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

$( "#new-level-confirmation-discard" ).click(function ( event ) {
  event.preventDefault();
  engine.trigger("Event Clear Level");
  $("#new-level-confirmation-container").fadeOut(250, function() {
    engine.trigger("Event Hide Menu");
  });
})

// Quit confirmation menu
$( "#quit-confirmation-cancel" ).click(function( event ) {
  event.preventDefault();
  $("#save-confirmation-container").fadeOut(250, function() {
    $("#main-menu-container").delay(50).fadeIn(250);
  });
});

// Get row of item that is currently looked at
var currentRow = -1;

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

    if (currentHoveredItem.html() && currentHoveredItem != selectedItem) {
      engine.trigger("Print Line", "Changing hover item");

      if (currentHoveredItem.html()) {
        currentHoveredItem.html(currentHoveredItem.html().replace(/«|»/g, ''));
      }
      currentHoveredItem.removeClass("hovered");
      selectedItem.addClass("hovered");
      selectedItem.prepend("» ");
      selectedItem.append(" «");
    }
  }
});

// Click menu item
engine.on('MenuClicked', function() {
  var activeItem = $(".hovered:visible");

  activeItem.click();
});

// When menu is shown
engine.on('MenuVisibilityChanged', function( isShown ) {
  if (isShown) {
    $( "#save-confirmation-container").hide();
    $( "#save-container").hide();
    $( "#load-container").hide();
    $( "#settings-container").hide();
    $( "#new-level-confirmation-container").hide();
    $( "#load-complete-container" ).hide();
    $(" #main-menu-container").fadeIn();
  }
});

// Load complete!
engine.on('LevelLoaded', function() {
  $("#load-container").fadeOut(250, function() {
    $("#load-complete-container").delay(50).fadeIn(250, function() {
      $("#load-complete-container").delay(2000).fadeOut();
    });
  });
});

// Load complete!
engine.on('LevelSaved', function() {
  $("#save-container").fadeOut(250, function() {
    $("#save-complete-container").delay(50).fadeIn(250, function() {
      $("#save-complete-container").delay(2000).fadeOut();
    });
  });
});

// Metadata loaded!
engine.on('MetadataLoaded', function(levelName, metadata) {
  if (levelName == 'level1') {
    $("#load-level-modified-1").html(metadata);
    $("#save-level-modified-1").html(metadata);
  }
  else if (levelName == 'level2') {
    $("#load-level-modified-2").html(metadata);
    $("#save-level-modified-2").html(metadata);
  }
  else if (levelName == 'level3') {
    $("#load-level-modified-3").html(metadata);
    $("#save-level-modified-3").html(metadata);
  }
  else if (levelName == 'level4') {
    $("#load-level-modified-4").html(metadata);
    $("#save-level-modified-4").html(metadata);
  }
  else if (levelName == 'level5') {
    $("#load-level-modified-5").html(metadata);
    $("#save-level-modified-5").html(metadata);
  }
  else if (levelName == 'level6') {
    $("#load-level-modified-6").html(metadata);
    $("#save-level-modified-6").html(metadata);
  }
  else if (levelName == 'level7') {
    $("#load-level-modified-7").html(metadata);
    $("#save-level-modified-7").html(metadata);
  }
  else if (levelName == 'level8') {
    $("#load-level-modified-8").html(metadata);
    $("#save-level-modified-8").html(metadata);
  }
  else if (levelName == 'level9') {
    $("#load-level-modified-9").html(metadata);
    $("#save-level-modified-9").html(metadata);
  }
  else if (levelName == 'level10') {
    $("#load-level-modified-10").html(metadata);
    $("#save-level-modified-10").html(metadata);
  }
})

var counter = 0;
setInterval(function() {
  engine.trigger("Event Save Level", "Test " + counter);
  counter++;
}, 1000);



// Test selections
// testXPos = 0.0;

// setInterval(function() {
//   testXPos += 0.05
//   if (testXPos >= 1.0) {
//     testXPos -= 1;
//   }
//   var newRow = Math.ceil(testXPos * 12);
//   if (newRow == 0) {
//     newRow = 1;
//   }

//   // $(".menu-button-item").removeClass("hovered");

//   var selectedItem = null;
//   if (currentRow != newRow) {
//     currentRow = newRow;
//     switch (currentRow) {
//       case 1:
//         selectedItem = $(".highlight-row-1:visible").find(".menu-button-item");
//         break;
//       case 2:
//         selectedItem = $(".highlight-row-2:visible").find(".menu-button-item");
//         break;
//       case 3:
//         selectedItem = $(".highlight-row-3:visible").find(".menu-button-item");
//         break;
//       case 4:
//         selectedItem = $(".highlight-row-4:visible").find(".menu-button-item");
//         break;
//       case 5:
//         selectedItem = $(".highlight-row-5:visible").find(".menu-button-item");
//         break;
//       case 6:
//         selectedItem = $(".highlight-row-6:visible").find(".menu-button-item");
//         break;
//       case 7:
//         selectedItem = $(".highlight-row-7:visible").find(".menu-button-item");
//         break;
//       case 8:
//         selectedItem = $(".highlight-row-8:visible").find(".menu-button-item");
//         break;
//       case 9:
//         selectedItem = $(".highlight-row-9:visible").find(".menu-button-item");
//         break;
//       case 10:
//         selectedItem = $(".highlight-row-10:visible").find(".menu-button-item");
//         break;
//       case 11:
//         selectedItem = $(".highlight-row-11:visible").find(".menu-button-item");
//         break;
//       case 12:
//         selectedItem = $(".highlight-row-12:visible").find(".menu-button-item");
//         break;
//       default:
//         selectedItem = $(".highlight-row-1:visible").find(".menu-button-item");
//         break;
//     }

//     var currentHoveredItem = $(".hovered:visible");

//     if (currentHoveredItem != selectedItem) {
//       engine.trigger("Print Line", "Changing hover item");

//       if (currentHoveredItem.html()) {
//         currentHoveredItem.html(currentHoveredItem.html().replace(/«|»/g, ''));
//       }
//       currentHoveredItem.removeClass("hovered");
//       selectedItem.addClass("hovered");
//       selectedItem.prepend("» ");
//       selectedItem.append(" «");
//     }
//   }
// }, 300);