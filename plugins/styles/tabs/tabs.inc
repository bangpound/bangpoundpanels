<?php


/**
 * @file
 * Definition of the 'Tabs' panel style.
 */

// Plugin definition
$plugin = array(
  'title' => t('Tabs'),
  'description' => t('Show panel panes in a region as tabs.'),
  'render pane' => 'panels_naked_style_render_pane',
  'render region' => 'bangpoundpanels_tabs_style_render_region',
);

/**
 * Render callback.
 *
 * @ingroup themeable
 */
function theme_bangpoundpanels_tabs_style_render_region($vars) {
  $display = $vars['display'];
  $region_id = $vars['region_id'];
  $owner_id = $vars['owner_id'];
  $panes = $vars['panes'];

  $tab_id = 'tabs-' . $owner_id . '-' . $region_id;

  $element = array(
    '#prefix' => '<div id="' . $tab_id . '">',
    '#suffix' => '</div>',
    '#attached' => array(
      'library' => array(array('system', 'ui.tabs')),
      'js' => array(
        drupal_get_path('module', 'bangpoundpanels') . '/plugins/styles/tabs/tabs.js' => array('type' => 'file'),
      ),
    ),
  );

  $settings = array();
  $settings['panelsTabs']['tabsID'][] = $tab_id;

  $element['#attached']['js'][] = array(
    'type' => 'setting',
    'data' => $settings,
  );

  // Get the pane titles.
  $items = array();
  $delta = 1;
  foreach ($display->panels[$region_id] as $pane_id) {
    // Make sure the pane exists.
    if (!empty($panes[$pane_id])) {
      $title = bangpoundpanels_pane_titles($display->did, $pane_id);
      $title = $title ? $title : t('Tab @delta', array('@delta' => $delta));

      if (is_array($title) && isset($title['#markup'])) {
        $title = filter_xss(render($title), array());
      }
      if (!is_array($title)) {
        $title = array(
          '#type' => 'link',
          '#title' => $title,
          '#href' => '#'. $tab_id .'-'. $delta,
          '#options' => array(
            'absolute' => TRUE,
            'external' => TRUE,
          ),
        );
      }
      else if (is_array($title) && isset($title['#type']) && $title['#type'] == 'link') {
        $title['#href'] = '#'. $tab_id .'-'. $delta;
        $title['#options']['absolute'] = TRUE;
        $title['#options']['external'] = TRUE;
      }
      $items[] = render($title);
      ++$delta;
    }
  }

  $element['tabs_title'] = array('#theme' => 'item_list', '#items' => $items);

  $items = array();
  $delta = 1;
  foreach ($panes as $pane_id => $item) {
    $element['tabs_content'][$pane_id] = array(
      '#prefix' => '<div id="' . $tab_id . '-' . $delta . '">',
      '#suffix' => '</div>',
      '#markup' => $item,
    );
    ++$delta;
  }

  return drupal_render($element);
}
