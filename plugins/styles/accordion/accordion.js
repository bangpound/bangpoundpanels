(function ($) {

Drupal.behaviors.PanelsAccordionStyle = {
  attach: function (context, settings) {
    $.each(Drupal.settings.accordion, function (index) {
      $(index).accordion(this);
    });
  }
}

})(jQuery);
