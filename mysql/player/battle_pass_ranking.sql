SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for battle_pass_ranking
-- ----------------------------
DROP TABLE IF EXISTS `battle_pass_ranking`;
CREATE TABLE `battle_pass_ranking`  (
  `battle_pass_id` int(11) NOT NULL,
  `player_name` varchar(255) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `finish_time` datetime(0) NOT NULL,
  PRIMARY KEY (`battle_pass_id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = utf8 COLLATE = utf8_unicode_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
