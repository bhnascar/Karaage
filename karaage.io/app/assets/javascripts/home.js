// Place all the behaviors and hooks related to the matching controller here.
// All this logic will automatically be available in application.js.

// $(document).ready(function(){

//   var scroll_start = 0;
//   var startchange = $('#home-level-editing-header');
//   var offset = startchange.offset();
//   $(".navbar-translucent").css('background-color', 'rgba(55,55,55,0.6)');
//   if (startchange.length){
//     var isDark = false;
//     $(document).scroll(function() { 
//       scroll_start = $(this).scrollTop();
//       if(scroll_start > offset.top) {
//         if (isDark) {
//           $(".navbar-translucent").css('background-color', 'rgba(55,55,55,0.9)');
//           $(".navbar-inverse .navbar-nav > li > a").css('color', '#bbb')
//           isDark = false;
//           console.log("Changed color to dark");
//         }
//       } else {
//         if (!isDark) {
//           $(".navbar-translucent").css('background-color', 'rgba(55,55,55,0.6)');
//           $(".navbar-inverse .navbar-nav > li > a").css('color', '#ddd')
//           isDark = true;
//           console.log("Changed color to light");
//         }
//       }
//     });
//   }
// });