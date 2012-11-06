/*jshint forin:true, noarg:true, noempty:true, eqeqeq:true, bitwise:true, undef:true, curly:true, browser:true, jquery:true, indent:2, maxerr:50 */
/*global Drupal:false, jQuery:false */
(function ($) {

  /**
   * JS related to the tabs in the Panels tabs.
   */
  Drupal.behaviors.PanelsAccordionStyle = {
    attach: function (context, settings) {
      $.each(settings.accordion, function (index) {
        $(index, context).once().accordion(this);
      });
    }
  };

})(jQuery);
