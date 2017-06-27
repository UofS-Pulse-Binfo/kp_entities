<?php
/**
 * @file
 * Create Tripal Content types used by KnowPulse.
 */

/**
 * Submits a Tripal Job to Create KnowPulse Tripal Content Types.
 */
function kp_entities_add_types_job() {
  global $user;
  $output = '';

  $job = new TripalJob();
  $job->create(array(
    'job_name' => 'Create KnowPulse Content Types',
      'modulename' => 'kp_entities',
      'callback' => 'kp_entities_create_content_types_job',
      'arguments' => array(),
      'uid' => $user->uid,
      'priority' => 10,
      'includes' => array(
        drupal_get_path('module', 'kp_entities') . '/includes/job.create_tripal_types'
      ),
  ));

  $jobs_url = url("admin/tripal/tripal_jobs");
  drupal_set_message(t("Check the <a href='!jobs_url'>jobs page</a> for status.",
      array('!jobs_url' => $jobs_url)));
  drupal_set_message(t("You can execute the job queue manually on the command line " .
      "using the following Drush command: <br>drush trp-run-jobs --username=%uname --root=%base_path",
      array('%base_path' => DRUPAL_ROOT, '%uname' => $user->name)));

  $output .= '<p>This page submits a Tripal Job to create all the Tripal Content Types pertinent to KnowPulse. If some of the types already exist then it will only add the missing Tripal Content Types.</p>';

  $output .= "<h3>KnowPulse Content Types</h3>\n<ul>\n";
  $types = kp_entities_types_list();
  foreach ($types as $type) {
    $output .= "  <li>" . $type['label'] . " (" . $type['vocabulary'] . ':' . $type['accession'] . ")</li>\n";
  }
  $output .= '</ul>';

  return $output;
}

/**
 * Creates all the KnowPulse Tripal Content Types.
 * Expected to be run as a Tripal job.
 */
function kp_entities_create_content_types_job() {

  $types = kp_entities_types_list();
  foreach ($types as $type) {

    $term = $bundle = NULL;

    // First create the Tripal Term (Example: Genetic Marker).
    $term = tripal_load_term_entity(array(
      'vocabulary' => $type['vocabulary'],
      'accession' => $type['accession']
    ));

    // If we have the term already then we might also have the bundle...
    if ($term) {
      $bundle = tripal_load_bundle_entity(array('term_id' => $term->id));
    }

    // If not, then create it.
    if (!$bundle) {
      $error = '';
      $bundle = tripal_create_bundle($type, $error);
      drush_log('Created '.$type['label'].' Tripal Content Type.', 'ok');
    }

  }
}
