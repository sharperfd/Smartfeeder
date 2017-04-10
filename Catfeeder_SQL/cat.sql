-- phpMyAdmin SQL Dump
-- version 4.6.1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Apr 10, 2017 at 04:31 AM
-- Server version: 5.7.12-log
-- PHP Version: 5.6.21

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `catfeeder`
--

-- --------------------------------------------------------

--
-- Table structure for table `cat`
--

CREATE TABLE `cat` (
  `TimeCatFeeding_CAT` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT 'เวลาที่แมวมากินอาหาร',
  `Auto_PK_CAT` int(10) NOT NULL COMMENT 'Auto ไอดีไปเรื่อยๆ',
  `name_CAT` varchar(80) NOT NULL,
  `TimeText` varchar(80) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `cat`
--

INSERT INTO `cat` (`TimeCatFeeding_CAT`, `Auto_PK_CAT`, `name_CAT`, `TimeText`) VALUES
('2017-04-03 08:24:37', 1, 'ฟ้า', 'วันที่ 03/04/2017 เวลา 15:24:37'),
('2017-04-03 08:25:51', 2, 'ฟ้า', 'วันที่ 03/04/2017 เวลา 15:25:51'),
('2017-04-06 10:09:54', 3, 'ฟ้า', 'วันที่ 06/04/2017 เวลา 17:09:54'),
('2017-04-06 10:14:00', 4, 'ฟ้า', 'วันที่ 06/04/2017 เวลา 17:14:00'),
('2017-04-06 10:15:44', 5, 'ฟ้า', 'วันที่ 06/04/2017 เวลา 17:15:44'),
('2017-04-06 10:21:20', 6, 'ฟ้า', 'วันที่ 06/04/2017 เวลา 17:21:20'),
('2017-04-06 10:31:48', 7, 'ฟ้า', 'วันที่ 06/04/2017 เวลา 17:31:48'),
('2017-04-06 10:39:36', 8, 'ฟ้า', 'วันที่ 06/04/2017 เวลา 17:39:36'),
('2017-04-06 10:51:52', 9, 'ฟ้า', 'วันที่ 06/04/2017 เวลา 17:51:52'),
('2017-04-06 10:52:19', 10, 'ฟ้า', 'วันที่ 06/04/2017 เวลา 17:52:19'),
('2017-04-06 14:18:56', 11, 'ฟ้า', 'วันที่ 06/04/2017 เวลา 21:18:56'),
('2017-04-06 14:20:43', 12, 'ฟ้า', 'วันที่ 06/04/2017 เวลา 21:20:43'),
('2017-04-06 14:21:36', 13, 'ฟ้า', 'วันที่ 06/04/2017 เวลา 21:21:36'),
('2017-04-06 14:21:44', 14, 'ฟ้า', 'วันที่ 06/04/2017 เวลา 21:21:44'),
('2017-04-06 14:23:43', 15, 'ฟ้า', 'วันที่ 06/04/2017 เวลา 21:23:43'),
('2017-04-06 14:24:11', 16, 'ฟ้า', 'วันที่ 06/04/2017 เวลา 21:24:11');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `cat`
--
ALTER TABLE `cat`
  ADD PRIMARY KEY (`Auto_PK_CAT`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `cat`
--
ALTER TABLE `cat`
  MODIFY `Auto_PK_CAT` int(10) NOT NULL AUTO_INCREMENT COMMENT 'Auto ไอดีไปเรื่อยๆ', AUTO_INCREMENT=17;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
