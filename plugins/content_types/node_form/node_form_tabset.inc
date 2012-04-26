<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  // only provides a single content type
  'single' => TRUE,
  'icon' => 'icon_node_form.png',
  'title' => t('Node form tabset'),
  'description' => t('Everything in the form that is not displayed by other content.'),
  'required context' => new ctools_context_required(t('Form'), 'node_form'),
  'category' => t('Form'),
);

/**
 * Output function for the 'node' content type. Outputs a node
 * based on the module and delta supplied in the configuration.
 */
function bangpoundpanels_node_form_tabset_content_type_render($subtype, $conf, $panel_args, &$context) {
  $block = new stdClass();
  $block->module = 'node_form';

  $block->delta = 'tabset';

  if (isset($context->form)) {
    $block->title = '';
    $block->content = $context->form['additional_settings'];
    $context->form['additional_settings']['#access'] = FALSE;
  }
  else {
    $block->content = t('Node form tabset.');
  }

  return $block;
}

function bangpoundpanels_node_form_tabset_content_type_admin_title($subtype, $conf, $context) {
  return t('"@s" tab set', array('@s' => $context->identifier));
}

function bangpoundpanels_node_form_tabset_content_type_edit_form($form, &$form_state) {
  // provide a blank form so we have a place to override title
  // and stuff.
  return $form;
}
