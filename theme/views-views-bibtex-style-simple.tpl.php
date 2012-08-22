<?php
/**
 * @file views-views-bibtex-style-simple.tpl.php
 * Default template for the Views bibtex style plugin using the simple format
 *
 * Variables:
 * - $view: The View object.
 * - $rows: Hierachial array of key=>value pairs to convert to bibtex
 * - $options: Array of options for this style
 *
 * @ingroup views_templates
 */

if ($view->override_path) {
  // We're inside a live preview where the bibtex is pretty-printed.
  $bibtex = _views_bibtex_formatted($rows, $options, $html = TRUE);
  print "<code>$bibtex</code>";
}
else {
  $bibtex = _views_bibtex_formatted($rows, $options, $html = FALSE);
  if ($options['using_views_api_mode']) {
    // We're in Views API mode.
    print $bibtex;
  }
  else {
    // We want to send the bibtex as a server response so switch the content
    // type and stop further processing of the page.
    $content_type = ($options['content_type'] == 'default') ? 'text/plain' : $options['content_type'];
    drupal_set_header("Content-Type: $content_type; charset=utf-8");
    print $bibtex;
    //Don't think this is needed in .tpl.php files: module_invoke_all('exit');
    exit;
  }
}
