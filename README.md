# KnowPulse Entities
Creates and configures all Tripal Content Types used by KnowPulse.

## Loads the following ontologies:
- Sequence Ontology (SO): Used for chado.feature types (gene, sequence_variant, genetic_marker, chromosome, QTL, etc.) and variant types (SNP, MNP, Indel)
- Plant Ontology (PO; v2017-02-02): Used to annotate phenotypes.
- Plant Trait Ontology (TO; v2017-02-02): Used to annotate phenotypes.
- Lentil (CO_339; v2016-02-15), Chickpea (CO_338; v2016-02-15), Common Bean (CO_335; v2015-05-13) Crop Ontology: to annotate phenotypes.
- Crop Germplasm Ontology (CO_010; v2011-10-03): Used for stock.types (accession, cultivar, inbred line)

## Creates the following single controlled vocabulary terms:
| Vocabulary       | Term        | Accession |
|------------------|-------------|------------|
| Semantic Science | Study       | SIO:001066 |
| Semantic Science | Experiment  | SIO:000994 |
| EDAM             | Genetic map | data:1278  |

## Creates the following Tripal Content Types:
- chado.organism table (full table)
  - Organism (obi:organism)
- chado.project table (seperated using projectprop)
  - Research Project (semantic science ontology; study; SIO:001066)
  - Research Experiment (semantic science ontology; experiment; SIO:000994)
  - Genome Assembly (Sequence Ontology; genome)
- chado.publication (full table)
  - Publication (TPUB; Publication)
- chado.feature table (seperated using feature.type_id)
  - Chromosome (Sequence Ontology; pseudomolecule)
  - Contig (Sequence Ontology; contig)
  - Variant (Sequence Ontology; sequence_variant)
  - Genetic Marker  (Sequence Ontology; genetic_marker)
  - QTL (Sequence Ontology; QTL)
- chado.stock (seperated using stock.type_id)
  - Germplasm Accession (Crop ontology; accession; CO_010:0000044)
  - Breeding Cross (Crop ontology; generated germplasm(CO_010:0000255)?; breeder's line(CO_010:0000093)?, breeding material(CO_010:0000159)?)
  - Registered Varieties (Sequence Ontology; cultivar; CO_010:0000029)
  - Recombinant Imbred Line (Crop Ontology; inbred line; CO_010:0000162)
- chado.cvterm (specific cv_id)
  - Phenotypic Trait (Trait Ontology; plant trait)
- chado.featuremap (full table) 
  - Genetic Map (data onotology; Map)
