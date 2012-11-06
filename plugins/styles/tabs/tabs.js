/*jshint forin:true, noarg:true, noempty:true, eqeqeq:true, bitwise:true, undef:true, curly:true, browser:true, jquery:true, indent:2, maxerr:50 */
/*global Drupal:false, jQuery:false */
(function ($) {

  /**
   * JS related to the tabs in the Panels tabs.
   */
  Drupal.behaviors.panelsTabs = {
    attach: function (context, settings) {
      $.each(settings.panelsTabs, function (index) {
        var $tabs = $(index, context).prepend('<ul></ul>').tabs(this);

        $('.panel-pane', $tabs).once('panelsTabs', function (index) {
          var href = '#' + $(this).attr('id'),
            label = $(this).attr('title');
          $tabs.tabs('add', href, label, index);
        });
      });
    }
  };
})(jQuery);
