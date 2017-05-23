<?php
/**
 * @file
 * This file contains the Loading Ontologies Tripal Job.
 */

/**
 * Load Ontologies
 */
function kp_entities_load_ontologies_job($job = NULL) {

  $ontology_path = drupal_get_path('module', 'kp_entities') . '/ontologies/';

  $ontologies = array(
    'TO' => array(
      'name' => 'Plant Trait Ontology',
      'definition' => 'It is a controlled vocabulary to describe each trait as a distinguishable feature, characteristic, quality or phenotypic feature of a developing or mature individual.',
      'file' => 'to.obo',
    ),
    'PO' => array(
      'name' => 'Plant Ontology',
      'definition' => 'A controlled vocabulary to describe plant anatomy and the stages of plant development.',
      'file' => 'po.obo',
    ),
    'CO_010' => array(
      'name' => 'Crop Germplasm Ontology',
      'definition' => 'A controlled vocabulary to describe germplasm.',
      'file' => 'CO_010.obo',
    ),
    'CO_339' => array(
      'name' => 'Lentil Crop Ontology',
      'definition' => 'A controlled vocabulary to describe Lentil traits.',
      'file' => 'CO_339.obo'
    ),
    'CO_338' => array(
      'name' => 'Chickpea Crop Ontology',
      'definition' => 'A controlled vocabulary to describe Chickpea traits.',
      'file' => 'CO_338.obo'
    ),
    'CO_335' => array(
      'name' => 'Common Bean Crop Ontology',
      'definition' => 'A controlled vocabulary to describe Common Bean traits.',
      'file' => 'CO_335.obo'
    ),
  );

  foreach ($ontologies as $abbrev => $details) {

    // The OBO loader is aided by a list of ontologies that can be loaded.
    // First we should make sure that all our ontologies are in that list :-).
    $obo_id = db_query('SELECT obo_id FROM {tripal_cv_obo} WHERE name=:name',
      array(':name' => $details['name']))->fetchField();
    if (!$obo_id) {
      $obo_id = db_insert('tripal_cv_obo')
        ->fields(array(
          'name' => $details['name'],
          'path' => '{kp_entities}/ontologies/' . $details['file'],
        ))->execute();
    }

    // Check to see if the ontology has already been loaded :-).
    // Tripal names the cv's based on their namespace.
    // Thus we need to find the default namespace for each ontology.
    // Use grep to pull out the line with the default namespace.
    $command = 'grep "default-namespace" ' . $ontology_path . $details['file'];
    $line = shell_exec($command);

    // Now we extract the name from the line.
    preg_match('/default-namespace: (.*)$/', $line, $matches);
    $namespace = trim($matches[1]);

    // Now check to see if the controlled vocabulary is already loaded.
    $is_present = chado_query('SELECT true FROM {cv} WHERE name=:name', 
      array(':name' => $namespace))->fetchField(); 

    // If not, submit the loading job.
    if (!$is_present) {
      tripal_submit_obo_job(array('obo_id' => $obo_id));
    }
  }
}
