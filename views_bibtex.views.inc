<?php

/**
 * @file
 * Views style plugin to render nodes in the bibtex data format.
 *
 * @see views_plugin_style_bibtex.inc
 * @ingroup views_plugins
 */


/**
 * Implementation of hook_views_plugin().
 */
function views_bibtex_views_plugins() {
  $path = drupal_get_path('module', 'views_bibtex');
  return array(
    'module'  => 'views_bibtex',
    'style'   => array(                 // Declare the views_bibtex style plugin.
      'views_bibtex'      => array(
        'title'         => ('BibTeX'),
        'path'          => $path,
        'help'          => ('Displays nodes in the BibTeX bibliography format.'),
        'handler'         => 'views_plugin_style_bibtex',
        'theme'           => 'views_views_bibtex_style',
        'theme file'      => 'views_views_bibtex_style.theme.inc',
        'theme path'      => $path . '/theme',
        'additional themes' => array('views_views_bibtex_style_simple' => 'style'),
        'uses row plugin' => FALSE,
        'uses fields'     => TRUE,
        'uses options'    => TRUE,
        'type'            => 'normal',
        'help_topic'      => 'style-bibtex',
        'even empty'      => TRUE
      ),
    ),
  );
}
