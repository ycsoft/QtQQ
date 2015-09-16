/*
		openfire功能添加需要修改的sql字段

*/

--修改UserProvider
--UPDATE ofproperty SET propvalue='org.jivesoftware.openfire.user.HFUserProvider' WHERE name='provider.user.className';

--添加CA认证
INSERT INTO ofproperty VALUES ('ca.server.sxcz.url','http://localhost:6180/MessageService');
