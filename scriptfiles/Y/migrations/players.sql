/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

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
	(2, 6, 0, 0, 0, 0),
	(3, 7, 0, 5, 0, 0);
/*!40000 ALTER TABLE `player_statuses` ENABLE KEYS */;


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
