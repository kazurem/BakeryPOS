/*M!999999\- enable the sandbox mode */ 
-- MariaDB dump 10.19-12.1.2-MariaDB, for Linux (x86_64)
--
-- Host: localhost    Database: bakerydb
-- ------------------------------------------------------
-- Server version	12.1.2-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*M!100616 SET @OLD_NOTE_VERBOSITY=@@NOTE_VERBOSITY, NOTE_VERBOSITY=0 */;

--
-- Table structure for table `Customers`
--

DROP TABLE IF EXISTS `Customers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Customers` (
  `CustomerID` int(11) NOT NULL AUTO_INCREMENT,
  `FName` varchar(100) DEFAULT NULL,
  `LName` varchar(100) DEFAULT NULL,
  `ContactNum` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`CustomerID`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Customers`
--

LOCK TABLES `Customers` WRITE;
/*!40000 ALTER TABLE `Customers` DISABLE KEYS */;
set autocommit=0;
INSERT INTO `Customers` VALUES
(1,'Alice','Wonder','555-1001'),
(2,'Bob','Builder','555-1002'),
(3,'Charlie','Brown','555-1003'),
(4,'Diana','Prince','555-1004'),
(5,'Ethan','Hunt','555-1005');
/*!40000 ALTER TABLE `Customers` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `OrderDetails`
--

DROP TABLE IF EXISTS `OrderDetails`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `OrderDetails` (
  `OrderID` int(11) DEFAULT NULL,
  `ProductID` int(11) DEFAULT NULL,
  `Quantity` int(11) DEFAULT NULL,
  `Price` float DEFAULT NULL,
  KEY `OrderID` (`OrderID`),
  KEY `ProductID` (`ProductID`),
  CONSTRAINT `1` FOREIGN KEY (`OrderID`) REFERENCES `Orders` (`OrderID`),
  CONSTRAINT `2` FOREIGN KEY (`ProductID`) REFERENCES `Products` (`ProductID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `OrderDetails`
--

LOCK TABLES `OrderDetails` WRITE;
/*!40000 ALTER TABLE `OrderDetails` DISABLE KEYS */;
set autocommit=0;
INSERT INTO `OrderDetails` VALUES
(1,1,2,20),
(2,3,1,45),
(3,5,3,10);
/*!40000 ALTER TABLE `OrderDetails` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `Orders`
--

DROP TABLE IF EXISTS `Orders`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Orders` (
  `OrderID` int(11) NOT NULL AUTO_INCREMENT,
  `UserID` int(11) DEFAULT NULL,
  `OrderDate` date DEFAULT NULL,
  `TotalAmount` float DEFAULT NULL,
  PRIMARY KEY (`OrderID`),
  KEY `UserID` (`UserID`),
  CONSTRAINT `1` FOREIGN KEY (`UserID`) REFERENCES `Users` (`UserID`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Orders`
--

LOCK TABLES `Orders` WRITE;
/*!40000 ALTER TABLE `Orders` DISABLE KEYS */;
set autocommit=0;
INSERT INTO `Orders` VALUES
(1,2,'2026-01-18',45),
(2,3,'2026-01-19',120.5),
(3,2,'2026-01-19',30),
(4,5,'2026-01-20',15),
(5,3,'2026-01-20',200);
/*!40000 ALTER TABLE `Orders` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `PreOrderDetails`
--

DROP TABLE IF EXISTS `PreOrderDetails`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `PreOrderDetails` (
  `PreOrderID` int(11) DEFAULT NULL,
  `ProductID` int(11) DEFAULT NULL,
  `QuantityOrdered` int(11) DEFAULT NULL,
  KEY `PreOrderID` (`PreOrderID`),
  KEY `ProductID` (`ProductID`),
  CONSTRAINT `1` FOREIGN KEY (`PreOrderID`) REFERENCES `PreOrders` (`PreOrderID`),
  CONSTRAINT `2` FOREIGN KEY (`ProductID`) REFERENCES `Products` (`ProductID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `PreOrderDetails`
--

LOCK TABLES `PreOrderDetails` WRITE;
/*!40000 ALTER TABLE `PreOrderDetails` DISABLE KEYS */;
set autocommit=0;
INSERT INTO `PreOrderDetails` VALUES
(1,2,5),
(2,4,10),
(3,7,2);
/*!40000 ALTER TABLE `PreOrderDetails` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `PreOrders`
--

DROP TABLE IF EXISTS `PreOrders`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `PreOrders` (
  `PreOrderID` int(11) NOT NULL AUTO_INCREMENT,
  `CustomerID` int(11) DEFAULT NULL,
  `PreOrderDate` date DEFAULT NULL,
  `PickUpDate` date DEFAULT NULL,
  `UserID` int(11) DEFAULT NULL,
  PRIMARY KEY (`PreOrderID`),
  KEY `CustomerID` (`CustomerID`),
  KEY `UserID` (`UserID`),
  CONSTRAINT `1` FOREIGN KEY (`CustomerID`) REFERENCES `Customers` (`CustomerID`),
  CONSTRAINT `2` FOREIGN KEY (`UserID`) REFERENCES `Users` (`UserID`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `PreOrders`
--

LOCK TABLES `PreOrders` WRITE;
/*!40000 ALTER TABLE `PreOrders` DISABLE KEYS */;
set autocommit=0;
INSERT INTO `PreOrders` VALUES
(1,1,'2026-01-15','2026-01-22',4),
(2,2,'2026-01-16','2026-01-23',4),
(3,3,'2026-01-17','2026-01-24',4),
(4,4,'2026-01-18','2026-01-25',2),
(5,5,'2026-01-19','2026-01-26',2);
/*!40000 ALTER TABLE `PreOrders` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `Products`
--

DROP TABLE IF EXISTS `Products`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Products` (
  `ProductID` int(11) NOT NULL AUTO_INCREMENT,
  `ProductName` varchar(255) DEFAULT NULL,
  `Category` varchar(100) DEFAULT NULL,
  `PricePerUnit` decimal(10,2) DEFAULT 0.00,
  `StockQuantity` int(11) DEFAULT NULL,
  PRIMARY KEY (`ProductID`)
) ENGINE=InnoDB AUTO_INCREMENT=22 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Products`
--

LOCK TABLES `Products` WRITE;
/*!40000 ALTER TABLE `Products` DISABLE KEYS */;
set autocommit=0;
INSERT INTO `Products` VALUES
(1,'Rasgulla','Sweet',20.00,100),
(2,'Gulab Jamun','Sweet',15.00,150),
(3,'Chocolate Cake','Bakery',450.00,10),
(4,'Butter Croissant','Bakery',45.00,40),
(5,'Samosa','Savory',12.00,80),
(6,'Jalebi','Sweet',10.00,200),
(7,'Whole Wheat Bread','Bakery',35.00,25),
(8,'Kaju Katli','Sweet',30.00,300),
(9,'Paneer Puff','Savory',25.00,50),
(10,'Vanilla Muffin','Bakery',20.00,60),
(11,'Barfi','Sweet',18.00,120),
(12,'Veg Patty','Savory',20.00,45),
(13,'Blueberry Cheesecake','Bakery',550.00,5),
(14,'Laddu','Sweet',12.00,180),
(15,'Garlic Bread','Bakery',60.00,15),
(16,'Chicken Quiche','Savory',85.00,12),
(17,'Milk Cake','Sweet',25.00,90),
(18,'Fruit Tart','Bakery',50.00,20),
(19,'Masala Chai Biscuit','Bakery',5.00,500),
(20,'Rasmalai','Sweet',40.00,70),
(21,'Almond Biscotti','Bakery',15.00,100);
/*!40000 ALTER TABLE `Products` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `Users`
--

DROP TABLE IF EXISTS `Users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Users` (
  `UserID` int(11) NOT NULL AUTO_INCREMENT,
  `FName` varchar(100) DEFAULT NULL,
  `LName` varchar(100) DEFAULT NULL,
  `ContactNum` varchar(20) DEFAULT NULL,
  `Birthday` date DEFAULT NULL,
  `Role` varchar(20) DEFAULT NULL,
  `Password` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`UserID`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Users`
--

LOCK TABLES `Users` WRITE;
/*!40000 ALTER TABLE `Users` DISABLE KEYS */;
set autocommit=0;
INSERT INTO `Users` VALUES
(1,'John','Doe','555-0101','1990-05-15','Admin','hashed_pw_1'),
(2,'Jane','Smith','555-0102','1988-10-22','Staff','hashed_pw_2'),
(3,'Mike','Ross','555-0103','1995-02-10','Staff','hashed_pw_3'),
(4,'Sarah','Connor','555-0104','1985-12-30','Manager','hashed_pw_4'),
(5,'Harvey','Specter','555-0105','1980-08-08','Staff','hashed_pw_5');
/*!40000 ALTER TABLE `Users` ENABLE KEYS */;
UNLOCK TABLES;
commit;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*M!100616 SET NOTE_VERBOSITY=@OLD_NOTE_VERBOSITY */;

-- Dump completed on 2026-01-20 16:07:49
