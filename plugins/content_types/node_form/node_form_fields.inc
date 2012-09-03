<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  // only provides a single content type
  'single' => TRUE,
  'icon' => 'icon_node_form.png',
  'title' => t('Node form fields'),
  'description' => t('Everything in the form that is not displayed by other content.'),
  'required context' => new ctools_context_required(t('Form'), 'node_form'),
  'category' => t('Form'),
  'defaults' => array(
    'fields' => '',
  ),
);

/**
 * Output function for the 'node' content type. Outputs a node
 * based on the module and delta supplied in the configuration.
 */
function bangpoundpanels_node_form_fields_content_type_render($subtype, $conf, $panel_args, &$context) {
  $block = new stdClass();
  $block->module = 'node_form';

  $block->delta = 'fields';

  if (isset($context->form)) {
    foreach (explode(',', $conf['fields']) as $field) {
      $block->title = '';
      if (isset($context->form[$field])) {
        $block->content[$field] = $context->form[$field];
        $context->form[$field]['#access'] = FALSE;
      }
    }
  }
  else {
    $block->content = t('Node form fields.');
  }

  return $block;
}

function bangpoundpanels_node_form_fields_content_type_admin_title($subtype, $conf, $context) {
  return t('"@s" fields', array('@s' => $context->identifier));
}

function bangpoundpanels_node_form_fields_content_type_edit_form($form, &$form_state) {
  // provide a blank form so we have a place to override title
  // and stuff.
  $conf = $form_state['conf'];

  $form['fields'] = array(
    '#type' => 'textfield',
    '#default_value' => $conf['fields'],
    '#title' => t('Fields'),
  );

  return $form;
}


function bangpoundpanels_node_form_fields_content_type_edit_form_submit($form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}
