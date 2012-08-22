<?php
/**
 * @file views-views-bibtex-style-simple.tpl.php
 * Default template for the Views BibTeX style plugin using the simple format
 *
 * Variables:
 * - $view: The View object.
 * - $rows: Hierachial array of key=>value pairs to convert to BibTeX
 * - $options: Array of options for this style
 *
 * @ingroup views_templates
 */

if ($view->override_path) {
  // We're inside a live preview where the BibTeX is pretty-printed.
  $bibtex = _views_bibtex_formatted($rows, $options, $html = TRUE);
  print "<code>$bibtex</code>";
}
else {
  $bibtex = _views_bibtex_formatted($rows, $options, $html = FALSE);
  if ($options['remove_newlines']) {
    $bibtex = preg_replace(array("/\n/"), '', $bibtex);
  }
  if ($options['using_views_api_mode']) {
    // We're in Views API mode.
    print $bibtex;
  }
  else {
    // We want to send the BibTeX as a server response so switch the content
    // type and stop further processing of the page.
    $content_type = ($options['content_type'] == 'default') ? 'text/plain' : $options['content_type'];
    drupal_add_http_header("Content-Type", "$content_type; charset=utf-8");
    print $bibtex;
    //Don't think this is needed in .tpl.php files: module_invoke_all('exit');
    exit;
  }
}
