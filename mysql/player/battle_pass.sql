SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for battle_pass
-- ----------------------------
DROP TABLE IF EXISTS `battle_pass`;
CREATE TABLE `battle_pass`  (
  `player_id` int(11) NOT NULL,
  `mission_id` int(11) NOT NULL,
  `battle_pass_id` int(11) NOT NULL,
  `extra_info` int(11) NULL DEFAULT NULL,
  `completed` int(1) NULL DEFAULT NULL,
  PRIMARY KEY (`mission_id`, `battle_pass_id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = utf8 COLLATE = utf8_unicode_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
