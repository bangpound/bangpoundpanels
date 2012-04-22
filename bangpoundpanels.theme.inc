<?php

/**
 * Preprocess the add content link used in the modal.
 */
function template_preprocess_panels_add_content_link__preview(&$vars) {
  $vars['title'] = filter_xss_admin($vars['content_type']['title']);
  $vars['description'] = isset($vars['content_type']['description']) ? $vars['content_type']['description'] : $title;
  $vars['icon'] = ctools_content_admin_icon($vars['content_type']);
  $vars['url'] = $vars['renderer']->get_url('add-pane', $vars['region'], $vars['content_type']['type_name'], $vars['content_type']['subtype_name']);

  $vars['image_button'] = ctools_ajax_image_button($vars['icon'], $vars['url'], $vars['description'], 'panels-modal-add-config');
  $vars['text_button'] = ctools_ajax_text_button($vars['title'], $vars['url'], $vars['description'], 'panels-modal-add-config');

  error_log('test');
}
