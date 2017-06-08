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
        module_load_include('inc', 'kp_entities', 'includes/job.create_tripal_types')
      ),
  ));

  $output .= '<div class="messages status">Run the Tripal Job to create KnowPulse Content Types.</div>';
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
