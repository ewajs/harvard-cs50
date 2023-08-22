-- MySQL dump 10.13  Distrib 5.5.41, for debian-linux-gnu (i686)
--
-- Host: localhost    Database: pset7
-- ------------------------------------------------------
-- Server version	5.5.41-0ubuntu0.14.04.1-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `history`
--

DROP TABLE IF EXISTS `history`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `history` (
  `transid` int(64) NOT NULL AUTO_INCREMENT,
  `id` int(64) NOT NULL,
  `date` datetime NOT NULL,
  `action` varchar(10) COLLATE utf8_unicode_ci NOT NULL,
  `symbol` varchar(10) COLLATE utf8_unicode_ci NOT NULL,
  `amount` int(64) NOT NULL,
  `price` decimal(65,4) NOT NULL,
  PRIMARY KEY (`transid`)
) ENGINE=InnoDB AUTO_INCREMENT=34 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `history`
--

LOCK TABLES `history` WRITE;
/*!40000 ALTER TABLE `history` DISABLE KEYS */;
INSERT INTO `history` VALUES (1,9,'2015-05-04 02:36:19','BUY','GOOG',1,538.0000),(2,9,'2015-05-09 11:42:05','SELL','AAPL',70,128.0000),(3,9,'2015-05-09 11:44:00','SELL','GOOG',6,538.2200),(4,9,'2015-05-09 11:46:14','SELL','GOOG',100,538.2200),(5,9,'2015-05-09 12:13:02','BUY','GOOG',3,538.2200),(6,9,'2015-05-09 12:37:16','BUY','MSFT',322,47.7500),(7,9,'2015-05-09 12:37:42','SELL','MSFT',1922,47.7500),(8,9,'2015-05-09 12:57:47','BUY','A',207,42.5000),(9,9,'2015-05-09 12:58:34','SELL','A',812,42.5000),(10,9,'2015-05-09 12:59:09','BUY','MSFT',300,47.7500),(11,9,'2015-05-09 16:16:33','SELL','AAPL',300,127.6200),(12,9,'2015-05-09 16:16:59','BUY','AAPL',500,127.6200),(13,9,'2015-05-09 16:18:09','SELL','AAPL',500,127.6200),(14,9,'2015-05-09 16:18:24','BUY','AAPL',314,127.6200),(15,9,'2015-05-09 16:46:45','SELL','AAPL',314,127.6200),(16,9,'2015-05-09 16:47:05','BUY','AAPL',271,127.6200),(17,9,'2015-05-09 16:50:46','SELL','AAPL',271,127.6200),(18,9,'2015-05-09 16:51:23','BUY','AAPL',173,127.6200),(19,9,'2015-05-09 16:55:18','SELL','AAPL',173,127.6200),(20,9,'2015-05-09 16:55:33','BUY','AAPL',161,127.6200),(21,9,'2015-05-09 17:01:12','SELL','AAPL',161,127.6200),(22,9,'2015-05-09 17:01:25','BUY','AAPL',173,127.6200),(23,9,'2015-05-09 17:02:32','BUY','AAPL',222,127.6200),(24,9,'2015-05-09 17:04:46','BUY','AAPL',333,127.6200),(25,9,'2015-05-09 17:05:21','BUY','AAPL',111,127.6200),(26,9,'2015-05-09 17:08:17','BUY','GOOG',1,538.2200),(27,9,'2015-05-09 17:12:22','BUY','GOOG',2,538.2200),(28,9,'2015-05-09 17:18:53','BUY','GOOG',4,538.2200),(29,9,'2015-05-09 19:03:24','BUY','GOOG',4,538.2200),(30,11,'2015-05-09 20:04:55','BUY','MSFT',100,47.7500),(31,11,'2015-05-09 20:05:42','BUY','AAPL',4,127.6200),(32,11,'2015-05-09 20:07:21','BUY','GOOG',3,538.2200),(33,11,'2015-05-09 20:09:14','BUY','GOOG',1,538.2200);
/*!40000 ALTER TABLE `history` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `stocks`
--

DROP TABLE IF EXISTS `stocks`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `stocks` (
  `id` int(11) NOT NULL,
  `symbol` varchar(10) COLLATE utf8_unicode_ci NOT NULL,
  `shares` int(11) NOT NULL,
  PRIMARY KEY (`id`,`symbol`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `stocks`
--

LOCK TABLES `stocks` WRITE;
/*!40000 ALTER TABLE `stocks` DISABLE KEYS */;
INSERT INTO `stocks` VALUES (1,'NOC',20),(2,'BAC',50),(3,'MSFT',100),(4,'MCD',70),(5,'XOM',120),(6,'ATML',200),(6,'NYT',100),(7,'HD',50),(7,'YHOO',150),(9,'AAPL',839),(9,'AAT',5),(9,'FREE',1156),(9,'GOOG',335),(9,'MSFT',603),(11,'AAPL',4),(11,'GOOG',4),(11,'MSFT',100);
/*!40000 ALTER TABLE `stocks` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `hash` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `cash` decimal(65,4) unsigned NOT NULL DEFAULT '0.0000',
  `mail` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'belindazeng','$1$50$oxJEDBo9KDStnrhtnSzir0',10000.0000,''),(2,'caesar','$1$50$GHABNWBNE/o4VL7QjmQ6x0',10000.0000,''),(3,'jharvard','$1$50$RX3wnAMNrGIbgzbRYrxM1/',10000.0000,''),(4,'malan','$1$50$lJS9HiGK6sphej8c4bnbX.',10000.0000,''),(5,'rob','$1$HA$l5llES7AEaz8ndmSo5Ig41',10000.0000,''),(6,'skroob','$1$50$euBi4ugiJmbpIbvTTfmfI.',10000.0000,''),(7,'zamyla','$1$50$uwfqB45ANW.9.6qaQ.DcF.',10000.0000,''),(9,'eze','$1$aQy2aoIx$EF7TJ2jQAi9LOWyKHL0Ke/',13766.5534,'ezequiel.wajs@gmail.com'),(10,'silvia','$1$Gq6FZ5g7$Q1sjbNCXgupVXcnElPTpv1',10000.0000,''),(11,'ewajs','$1$N3edZjhd$9P42rkQ0dcrz3qxO2ELvF1',2561.6400,'eze@eze.com');
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2015-05-09 20:10:25
