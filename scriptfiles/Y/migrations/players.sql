
/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE TABLE IF NOT EXISTS `objects` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `model` bigint(20) unsigned NOT NULL DEFAULT '0',
  `X` float NOT NULL DEFAULT '0',
  `Y` float NOT NULL DEFAULT '0',
  `Z` float NOT NULL DEFAULT '0',
  `RX` float NOT NULL DEFAULT '0',
  `RY` float NOT NULL DEFAULT '0',
  `RZ` float NOT NULL DEFAULT '0',
  `world` int(11) NOT NULL DEFAULT '-1',
  `interior` int(11) NOT NULL DEFAULT '-1',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;

/*!40000 ALTER TABLE `objects` DISABLE KEYS */;
INSERT INTO `objects` (`id`, `model`, `X`, `Y`, `Z`, `RX`, `RY`, `RZ`, `world`, `interior`) VALUES
  (1, 2152, 0, 0, 15, 0, 0, 0, 0, 0),
  (2, 2152, 5, 0, 10, 0, 0, 0, 0, 0);
/*!40000 ALTER TABLE `objects` ENABLE KEYS */;


CREATE TABLE IF NOT EXISTS `players` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(25) NOT NULL,
  `password` varchar(64) NOT NULL,
  `salt` varchar(64) NOT NULL,
  `created_at` datetime NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;

/*!40000 ALTER TABLE `players` DISABLE KEYS */;
INSERT INTO `players` (`id`, `name`, `password`, `salt`, `created_at`) VALUES
  (6, 'Misiur_Tarter', '291D7E2FD2CE65F4BA4AF939CE4E2C59F2B4E0A96C7FB95FD7B50BC1EE1122AB', 'Ixp01U5iE655Y35qe2G79UUr357aI41C', '2017-08-30 21:55:46'),
  (7, 'mega_man', '4C0D7DC42647D2C6588FCFF14DF801AD03809CE3C05BF55478CC14757E752CEE', 'D3uu3SA97D878twe2s07cM17V41pHc91', '2017-08-30 21:57:47');
/*!40000 ALTER TABLE `players` ENABLE KEYS */;


CREATE TABLE IF NOT EXISTS `player_statuses` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `player_id` bigint(20) unsigned NOT NULL DEFAULT '0',
  `developer` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `admin` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `money` int(10) unsigned NOT NULL DEFAULT '0',
  `vip` tinyint(3) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `player_id` (`player_id`),
  CONSTRAINT `player_id` FOREIGN KEY (`player_id`) REFERENCES `players` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;

/*!40000 ALTER TABLE `player_statuses` DISABLE KEYS */;
INSERT INTO `player_statuses` (`id`, `player_id`, `developer`, `admin`, `money`, `vip`) VALUES
  (2, 6, 0, 5, 0, 0),
  (3, 7, 0, 0, 0, 0);
/*!40000 ALTER TABLE `player_statuses` ENABLE KEYS */;


CREATE TABLE IF NOT EXISTS `rp_factions` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `creator_id` bigint(20) unsigned NOT NULL DEFAULT '0',
  `owner_id` bigint(20) unsigned NOT NULL DEFAULT '0',
  `name` varchar(32) NOT NULL DEFAULT '0',
  `money` bigint(20) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `player_id` (`owner_id`),
  KEY `owner_id` (`creator_id`),
  CONSTRAINT `FK_factions_players` FOREIGN KEY (`owner_id`) REFERENCES `players` (`id`),
  CONSTRAINT `FK_factions_players_2` FOREIGN KEY (`creator_id`) REFERENCES `players` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;

/*!40000 ALTER TABLE `rp_factions` DISABLE KEYS */;
INSERT INTO `rp_factions` (`id`, `creator_id`, `owner_id`, `name`, `money`) VALUES
  (5, 6, 6, 'Very good boys', 123),
  (6, 6, 6, 'Hello world faction', 10000),
  (7, 6, 6, 'Empty membership', 100000);
/*!40000 ALTER TABLE `rp_factions` ENABLE KEYS */;


CREATE TABLE IF NOT EXISTS `rp_faction_members` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `faction_id` bigint(20) unsigned NOT NULL DEFAULT '0',
  `player_id` bigint(20) unsigned NOT NULL DEFAULT '0',
  `rank` tinyint(3) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `faction_id_player_id` (`faction_id`,`player_id`),
  KEY `faction_id` (`faction_id`),
  KEY `player_id` (`player_id`),
  CONSTRAINT `FK__factions` FOREIGN KEY (`faction_id`) REFERENCES `rp_factions` (`id`),
  CONSTRAINT `FK__players` FOREIGN KEY (`player_id`) REFERENCES `players` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8;

/*!40000 ALTER TABLE `rp_faction_members` DISABLE KEYS */;
INSERT INTO `rp_faction_members` (`id`, `faction_id`, `player_id`, `rank`) VALUES
  (2, 6, 7, 0),
  (12, 5, 6, 0);
/*!40000 ALTER TABLE `rp_faction_members` ENABLE KEYS */;


CREATE TABLE IF NOT EXISTS `rp_faction_objects` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(50) DEFAULT NULL,
  `faction_id` bigint(20) unsigned NOT NULL DEFAULT '0',
  `object_id` bigint(20) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `object_id_uq` (`object_id`),
  KEY `faction_id` (`faction_id`),
  KEY `object_id` (`object_id`),
  CONSTRAINT `FK_faction_objects_factions` FOREIGN KEY (`faction_id`) REFERENCES `rp_factions` (`id`),
  CONSTRAINT `FK_faction_objects_objects` FOREIGN KEY (`object_id`) REFERENCES `objects` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;

/*!40000 ALTER TABLE `rp_faction_objects` DISABLE KEYS */;
INSERT INTO `rp_faction_objects` (`id`, `name`, `faction_id`, `object_id`) VALUES
  (3, NULL, 5, 1),
  (5, NULL, 5, 2);
/*!40000 ALTER TABLE `rp_faction_objects` ENABLE KEYS */;


CREATE TABLE IF NOT EXISTS `vehicles` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `player_id` bigint(20) unsigned NOT NULL,
  `model` mediumint(8) unsigned NOT NULL,
  `X` float NOT NULL,
  `Y` float NOT NULL,
  `Z` float NOT NULL,
  `R` float NOT NULL,
  `color_1` smallint(6) NOT NULL,
  `color_2` smallint(6) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `player_id` (`player_id`),
  CONSTRAINT `FK_vehicles_players` FOREIGN KEY (`player_id`) REFERENCES `players` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=utf8;

/*!40000 ALTER TABLE `vehicles` DISABLE KEYS */;
INSERT INTO `vehicles` (`id`, `player_id`, `model`, `X`, `Y`, `Z`, `R`, `color_1`, `color_2`) VALUES
  (11, 6, 587, 555.97, -1265.5, 17.24, 1.42, 0, 0);
/*!40000 ALTER TABLE `vehicles` ENABLE KEYS */;
/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
