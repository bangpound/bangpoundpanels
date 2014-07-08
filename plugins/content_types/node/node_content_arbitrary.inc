<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'single' => TRUE,
  'title' => t('Node content (arbitrary)'),
  'icon' => 'icon_node.png',
  'description' => t('Arbitrary properties of the referenced node.'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'category' => t('Node'),
  'defaults' => array(
    'override_title' => FALSE,
    'override_title_text' => '',
    'build_mode' => '',
    'identifier' => '',
    'property_path' => '',
    'link' => TRUE,
  ),
);

/**
 * Output function for the 'node' content type. Outputs a node
 * based on the module and delta supplied in the configuration.
 */
function bangpoundpanels_node_content_arbitrary_content_type_render($subtype, $conf, $panel_args, $context) {
  if (!empty($context) && empty($context->data)) {
    return;
  }

  $node = isset($context->data) ? clone($context->data) : NULL;
  $block = new stdClass();
  $block->module = 'node';
  $block->delta  = $node->nid;

  if (empty($node)) {
    $block->delta   = 'placeholder';
    $block->subject = t('Node title.');
    $block->content = t('Node content go here.');
  }
  else {
    $accessor = \Symfony\Component\PropertyAccess\PropertyAccess::createPropertyAccessor();

    if (!empty($conf['identifier'])) {
      $node->panel_identifier = $conf['identifier'];
    }

    $block->subject = $node->title;
    node_build_content($node, $conf['build_mode']);
    $block->content =  $accessor->getValue($node, $conf['property_path']);
  }

  if (!empty($conf['link']) && $node) {
    $block->title_link = "node/$node->nid";
  }
  return $block;
}

/**
 * Returns an edit form for the custom type.
 */
function bangpoundpanels_node_content_arbitrary_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $form['link'] = array(
    '#title' => t('Link title to node'),
    '#type' => 'checkbox',
    '#default_value' => $conf['link'],
    '#description' => t('Check here to make the title link to the node.'),
  );

  $entity = entity_get_info('node');
  $build_mode_options = array();
  foreach ($entity['view modes'] as $mode => $option) {
    $build_mode_options[$mode] = $option['label'];
  }

  $form['build_mode'] = array(
    '#title' => t('Build mode'),
    '#type' => 'select',
    '#description' => t('Select a build mode for this node.'),
    '#options' => $build_mode_options,
    '#default_value' => $conf['build_mode'],
  );

  $form['identifier'] = array(
    '#type' => 'textfield',
    '#default_value' => $conf['identifier'],
    '#title' => t('Identifier'),
    '#description' => t('Whatever is placed here will appear in @identifier, to help theme node content displayed on the panel', array('@identifier' => $node->panel_identifier)),
  );

  $form['property_path'] = array(
    '#type' => 'textfield',
    '#default_value' => $conf['property_path'],
    '#title' => t('Property path'),
    '#description' => t('A property path for an element on the node. For example, use <em>content</em> or <em>content[links]</em>. See the <a href="http://symfony.com/doc/current/components/property_access/introduction.html">Symfony documentation for the property access component</a> for more advice.'),
  );

  return $form;
}

function bangpoundpanels_node_content_arbitrary_content_type_edit_form_submit($form, &$form_state) {
  // Copy everything from our defaults.
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}

function bangpoundpanels_node_content_arbitrary_content_type_admin_title($subtype, $conf, $context) {
  return t('"@s" property @p', array('@s' => $context->identifier, '@p' => $conf['property_path']));
}

