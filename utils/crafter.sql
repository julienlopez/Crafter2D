-- phpMyAdmin SQL Dump
-- version 3.3.9
-- http://www.phpmyadmin.net
--
-- Serveur: localhost
-- Généré le : Sam 28 Janvier 2012 à 13:00
-- Version du serveur: 5.1.53
-- Version de PHP: 5.3.4

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Base de données: `crafter`
--

-- --------------------------------------------------------

--
-- Structure de la table `user`
--

DROP TABLE `user`;
CREATE TABLE `user` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `pseudo` text NOT NULL,
  `mdp` text NOT NULL,
  `position` text NOT NULL,
  `inventory` text NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

--
-- Contenu de la table `user`
--

INSERT INTO `user` (`id`, `pseudo`, `mdp`, `position`, `inventory`) VALUES
(1, 'epso', 'bouh', '{-6.9,11.1,0.152649}', '[{0;4},{2;10}]'),
(2, 'moi', 'bouh', '{-12.1,-0.9,1.80093}', '');
