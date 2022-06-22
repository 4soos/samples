local NAME = "upperTester"

local upperTester = Proto(NAME, "upperTester Protocol")

request = '00'
response = '80'

	
local GroupID_info = { 
	[0x00] =  "GENERAL",
	[0x01] =  "UDP",
	[0x02] =  "TCP",
	[0x03] =  "ICMP",
	[0x04] =  "ICMPv6",
	[0x05] =  "IP",
	[0x06] =  "IPv6",
	[0x07] =  "DHCP",
	[0x08] =  "DHCPv6",
	[0x09] =  "ARP",
	[0x0A] =  "NDP",
	[0x0B] =  "ETH",
	[0x0C] =  "PHY",}
local EVB_info = { 
	[0x00] =  "EVB=0",
	[0x01] =  "EVB=1",}
local GENERALGID00 = { 
	[0x01] =  "GET VERSION",
	[0x02] =  "START TEST",
	[0x03] =  "END TEST",}

local UDPGID01 = { 
	[0x00] =  "CLOSE SOCKET",
	[0x01] =  "CREATE AND BIND",
	[0x02] =  "SEND DATA",
	[0x03] =  "RECEIVE AND FORWARD",
	[0x06] =  "CONFIGURE SOCKET",
	[0x07] =  "SHUTDOWN",}
	
local TCPGID02 = { 
	[0x00] =  "CLOSE SOCKET",
	[0x01] =  "CREATE AND BIND",
	[0x02] =  "SEND DATA",
	[0x03] =  "RECEIVE AND FORWARD",
	[0x04] =  "LISTEN AND ACCEPT",
	[0x05] =  "CONNECT",
	[0x06] =  "CONFIGURE SOCKET",
	[0x07] =  "SHUTDOWN",}

local IMCPGID03 = { 
	[0x00] =  "ECHO REQUEST",}

local IMCPv6GID04 = { 
	[0x00] =  "ECHO REQUEST",}

local IPGID05 = { 
	[0x00] =  "STATIC ADDRESS",
	[0x01] =  "STATIC ROUTE",}

local IPv6GID06 = { 
	[0x00] =  "STATIC ADDRESS",
	[0x01] =  "STATIC ROUTE",}
	
local DHCPGID07 = { 
	[0x00] =  "INIT DHCP CLIENT",
	[0x01] =  "STOP DHCP CLIENT",
	[0x02] =  "SET DHCP OPTION",}

local DHCPv6GID08 = { 
	[0x00] =  "INIT DHCP CLIENT",
	[0x01] =  "STOP DHCP CLIENT",
	[0x02] =  "SET DHCP OPTION",}	
	
local ETHGID0B = { 
	[0x00] =  "INTERFACE UP",
	[0x01] =  "INTERFACE DOWN",}
	
local PHYGID0C = { 
	[0x00] =  "READ SIGNAL QUALITY",
	[0x01] =  "READ DIAG RESULT",
	[0x02] =  "ACTIVATE TEST MODE",
	[0x03] =  "SET PHY TX MODE",}	
	
local RequestOrResponse = {
	[0x00] =  "Request",
	[0x80] =  "Response",}


-- dissect packet
function upperTester.dissector (tvb, pinfo, tree)
end

-- register this dissector
DissectorTable.get("udp.port"):add(5010, upperTester)
DissectorTable.get("udp.port"):add(5001, upperTester)
DissectorTable.get("udp.port"):add(61471, upperTester)
DissectorTable.get("udp.port"):add(6001, upperTester)

local fields = upperTester.fields


	
	
	
	
	
fields.serviceID = ProtoField.uint16 (NAME .. ".ServiceID", "ServiceID", base.HEX)
fields.EVB = ProtoField.uint8 (NAME .. ".EVB", "EVB", base.HEX, EVB_info)
fields.GroupID = ProtoField.uint8 (NAME .. ".GroupID", "GroupID", base.HEX, GroupID_info)
fields.ServicePrimitiveID00 = ProtoField.uint8(NAME .. ".ServicePrimitiveID", "ServicePrimitiveID", base.HEX, GENERALGID00)
fields.ServicePrimitiveID01 = ProtoField.uint8(NAME .. ".ServicePrimitiveID", "ServicePrimitiveID", base.HEX, UDPGID01)
fields.ServicePrimitiveID02 = ProtoField.uint8(NAME .. ".ServicePrimitiveID", "ServicePrimitiveID", base.HEX, TCPGID02)
fields.ServicePrimitiveID03 = ProtoField.uint8(NAME .. ".ServicePrimitiveID", "ServicePrimitiveID", base.HEX, IMCPGID03)
fields.ServicePrimitiveID04 = ProtoField.uint8(NAME .. ".ServicePrimitiveID", "ServicePrimitiveID", base.HEX, IMCPv6GID04)
fields.ServicePrimitiveID05 = ProtoField.uint8(NAME .. ".ServicePrimitiveID", "ServicePrimitiveID", base.HEX, IPGID05)
fields.ServicePrimitiveID06 = ProtoField.uint8(NAME .. ".ServicePrimitiveID", "ServicePrimitiveID", base.HEX, IPv6GID06)
fields.ServicePrimitiveID07 = ProtoField.uint8(NAME .. ".ServicePrimitiveID", "ServicePrimitiveID", base.HEX, DHCPGID07)
fields.ServicePrimitiveID08 = ProtoField.uint8(NAME .. ".ServicePrimitiveID", "ServicePrimitiveID", base.HEX, DHCPv6GID08)
fields.ServicePrimitiveID0b = ProtoField.uint8(NAME .. ".ServicePrimitiveID", "ServicePrimitiveID", base.HEX, ETHGID0B)
fields.ServicePrimitiveID0c = ProtoField.uint8(NAME .. ".ServicePrimitiveID", "ServicePrimitiveID", base.HEX, PHYGID0C)


fields.Length = ProtoField.uint32(NAME .. ".Length", "Length", base.HEX)
fields.dc = ProtoField.uint32(NAME .. ".dc", "dc", base.HEX)
fields.ProtocolVersion = ProtoField.uint8(NAME .. ".ProtocolVersion", "ProtocolVersion", base.HEX)
fields.InterfaceVersion = ProtoField.uint8(NAME .. ".InterfaceVersion", "InterfaceVersion", base.HEX)
fields.TypeID = ProtoField.uint8(NAME .. ".TypeID", "TypeID", base.HEX, RequestOrResponse)
fields.ResultID = ProtoField.uint8(NAME .. ".ResultID", "ResultID", base.HEX)

fields.GENERAL01majorVer = ProtoField.uint16(NAME .. ".majorVer", "majorVer", base.HEX)
fields.GENERAL01minorVer = ProtoField.uint16(NAME .. ".minorVer", "minorVer", base.HEX)
fields.GENERAL01patchVer = ProtoField.uint16(NAME .. ".patchVer", "patchVer", base.HEX)

fields.GENERAL03tcId = ProtoField.uint16(NAME .. ".tcId", "tcId", base.HEX)

fields.UDPTCP00socketId = ProtoField.uint16(NAME .. ".socketId", "socketId", base.HEX)
fields.UDPTCP00abort = ProtoField.uint8(NAME .. ".abort", "abort", base.HEX)

fields.UDPTCP01doBind = ProtoField.uint8(NAME .. ".doBind", "doBind", base.HEX)
fields.UDPTCP01localPort = ProtoField.uint16(NAME .. ".localPort", "localPort", base.HEX)
fields.UDPTCP01ipN = ProtoField.uint16(NAME .. ".ipN", "ipN", base.HEX)
fields.UDPTCP01ipv4 = ProtoField.ipv4(NAME .. ".ipv4", "ipv4", base.HEX)
fields.UDPTCP01ipv6 = ProtoField.ipv6(NAME .. ".ipv6", "ipv6", base.HEX)

fields.UDPTCP01socketId = ProtoField.uint16(NAME .. ".socketId", "socketId", base.HEX)


fields.UDPTCP02socketId = ProtoField.uint16(NAME .. ".socketId", "socketId", base.HEX)
fields.UDPTCP02totalLen = ProtoField.uint16(NAME .. ".totalLen", "totalLen", base.HEX)
fields.UDPTCP02destPort = ProtoField.uint16(NAME .. ".destPort", "destPort", base.HEX)
fields.UDPTCP02flags = ProtoField.uint8(NAME .. ".flags", "flags", base.HEX)

fields.UDPTCP03socketId = ProtoField.uint16(NAME .. ".socketId", "socketId", base.HEX)
fields.UDPTCP03maxFwd = ProtoField.uint16(NAME .. ".maxFwd", "maxFwd", base.HEX)
fields.UDPTCP03maxLen = ProtoField.uint16(NAME .. ".maxLen", "maxLen", base.HEX)

fields.UDPTCP03dropCnt = ProtoField.uint16(NAME .. ".dropCnt", "dropCnt", base.HEX)

fields.TCP04listenSocketId = ProtoField.uint16(NAME .. ".listenSocketId", "listenSocketId", base.HEX)
fields.TCP04maxCon = ProtoField.uint16(NAME .. ".maxCon", "maxCon", base.HEX)

fields.TCP06socketId = ProtoField.uint16(NAME .. ".socketId", "socketId", base.HEX)
fields.TCP06paramId = ProtoField.uint16(NAME .. ".paramId", "paramId", base.HEX)

fields.PHY00sigQuality = ProtoField.uint8(NAME .. ".sigQuality", "sigQuality", base.HEX)

fields.PHY01diagResult = ProtoField.uint8(NAME .. ".diagResult", "diagResult", base.HEX)

fields.TCPUDP07socketId = ProtoField.uint16(NAME .. ".socketId", "socketId", base.HEX)
fields.TCPUDP07typeId = ProtoField.uint8(NAME .. ".typeId", "typeId", base.HEX)



function upperTester.dissector (tvb, pinfo, tree)
    local subtree = tree:add(upperTester, tvb())
    local offset = 0
    
    -- show protocol name in protocol column
    pinfo.cols.protocol = upperTester.name
    
    -- dissect field one by one, and add to protocol tree

	
	
    subtree:add(fields.serviceID, tvb(offset, 2))
    offset = offset + 2
	
	local GID = tvb(offset, 1)
	
	--print(GID>>7)
	GID = tonumber(tostring(GID),16)
	if(tonumber(tostring(GID))>=80)
	then
		subtree:add(fields.EVB, 1)
		subtree:add(fields.GroupID, GID-0X80)
	else
		subtree:add(fields.EVB, 0)
		subtree:add(fields.GroupID, GID)
	end
	
	
	GID = tvb(offset, 1)
    offset = offset + 1

	local PID = tvb(offset, 1)
	
	if('00' == tostring(GID))
	then
		subtree:add(fields.ServicePrimitiveID00, tvb(offset, 1))		
	end
	
	if('01' == tostring(GID))
	then
		subtree:add(fields.ServicePrimitiveID01, tvb(offset, 1))		
	end
	
	if('02' == tostring(GID))
	then
		subtree:add(fields.ServicePrimitiveID02, tvb(offset, 1))		
	end
	
	if('03' == tostring(GID))
	then
		subtree:add(fields.ServicePrimitiveID03, tvb(offset, 1))		
	end
	
	if('04' == tostring(GID))
	then
		subtree:add(fields.ServicePrimitiveID04, tvb(offset, 1))		
	end
	
	if('05' == tostring(GID))
	then
		subtree:add(fields.ServicePrimitiveID05, tvb(offset, 1))		
	end
	
	if('06' == tostring(GID))
	then
		subtree:add(fields.ServicePrimitiveID06, tvb(offset, 1))		
	end
	
	if('07' == tostring(GID))
	then
		subtree:add(fields.ServicePrimitiveID07, tvb(offset, 1))		
	end
	
	if('08' == tostring(GID))
	then
		subtree:add(fields.ServicePrimitiveID08, tvb(offset, 1))		
	end
	
	if('0b' == tostring(GID))
	then
		subtree:add(fields.ServicePrimitiveID0b, tvb(offset, 1))		
	end
	
	if('0c' == tostring(GID))
	then
		subtree:add(fields.ServicePrimitiveID0c, tvb(offset, 1))		
	end	
	
	offset = offset + 1
	
    subtree:add(fields.Length, tvb(offset, 4))
	offset = offset + 4
	subtree:add(fields.dc, tvb(offset, 4))
	offset = offset + 4
	subtree:add(fields.ProtocolVersion, tvb(offset, 1))
	offset = offset + 1
	subtree:add(fields.InterfaceVersion, tvb(offset, 1))
	offset = offset + 1
	local typeID = tvb(offset, 1)
	subtree:add(fields.TypeID, tvb(offset, 1))
	offset = offset + 1	
	subtree:add(fields.ResultID, tvb(offset, 1))
	offset = offset + 1

	--6.10.1 GET VERSION
	if(GENERAL == tostring(GID) and '01' == tostring(PID) and response == tostring(typeID))
	then
		subtree:add(fields.GENERALmajorVer, tvb(offset, 2))
		offset = offset + 2
		subtree:add(fields.GENERALminorVer, tvb(offset, 2))
		offset = offset + 2
		subtree:add(fields.GENERALpatchVer, tvb(offset, 2))
		offset = offset + 2
	end
	
	--6.10.3 END TEST
	if(GENERAL == tostring(GID) and '03' == tostring(PID) and request == tostring(typeID))
	then
		subtree:add(fields.GENERAL03tcId, tvb(offset, 2))
		offset = offset + 2
	end
	
	--6.10.4 CLOSE SOCKET
	if((UDP == tostring(GID) or TCP == tostring(GID))  and '00' == tostring(PID) and request == tostring(typeID))
	then
		subtree:add(fields.UDPTCP00socketId, tvb(offset, 2))
		offset = offset + 2	
		subtree:add(fields.UDPTCP00abort, tvb(offset, 1))
		offset = offset + 1
	end 
	
	--6.10.5 CREAT AND BIND
	if((UDP == tostring(GID) or TCP == tostring(GID))  and '01' == tostring(PID) and request == tostring(typeID))
	then
		subtree:add(fields.UDPTCP01doBind, tvb(offset, 1))
		offset = offset + 1	
		subtree:add(fields.UDPTCP01localPort, tvb(offset, 2))
		offset = offset + 2	
		local n = tvb(offset, 2)
		subtree:add(fields.UDPTCP01ipN, tvb(offset, 2))
		offset = offset + 2
		if('0004' == tostring(n))
		then
			subtree:add(fields.UDPTCP01ipv4, tvb(offset, 4))
			offset = offset + 4
		end
		if('0010' == tostring(n))
		then
			subtree:add(fields.UDPTCP01ipv6, tvb(offset, 16))
			offset = offset + 16	
		end
	end 
	
	if((UDP == tostring(GID) or TCP == tostring(GID))  and '01' == tostring(PID) and response == tostring(typeID))
	then
		subtree:add(fields.UDPTCP01socketId, tvb(offset, 2))
		offset = offset + 2
	end
	
	--6.10.6 SEND DATA
	if((UDP == tostring(GID) or TCP == tostring(GID))  and '02' == tostring(PID) and request == tostring(typeID))
	then
		subtree:add(fields.UDPTCP02socketId, tvb(offset, 2))
		offset = offset + 2
		subtree:add(fields.UDPTCP02totalLen, tvb(offset, 2))
		offset = offset + 2
		subtree:add(fields.UDPTCP02destPort, tvb(offset, 2))
		offset = offset + 2
		
		local n = tvb(offset, 2)
		subtree:add(fields.UDPTCP01ipN, tvb(offset, 2))
		offset = offset + 2
		print(tostring(n))
		if('0004' == tostring(n))
		then
			subtree:add(fields.UDPTCP01ipv4, tvb(offset, 4))
			offset = offset + 4
		end
		if('0010' == tostring(n))
		then
			subtree:add(fields.UDPTCP01ipv6, tvb(offset, 16))
			offset = offset + 16	
		end
		
		subtree:add(fields.UDPTCP02flags, tvb(offset, 1))
		offset = offset + 1
	end
	
	--6.10.7 RECEIVE AND FORWARD
	if((UDP == tostring(GID) or TCP == tostring(GID))  and '03' == tostring(PID) and request == tostring(typeID))
	then
		subtree:add(fields.UDPTCP03socketId, tvb(offset, 2))
		offset = offset + 2
		subtree:add(fields.UDPTCP03maxFwd, tvb(offset, 2))
		offset = offset + 2
		subtree:add(fields.UDPTCP03maxLen, tvb(offset, 2))
		offset = offset + 2
	end
	
	if((UDP == tostring(GID) or TCP == tostring(GID))  and '03' == tostring(PID) and response == tostring(typeID))
	then
		subtree:add(fields.UDPTCP03dropCnt, tvb(offset, 2))
		offset = offset + 2
	end
	
	--6.10.8 LISTEN AND ACCEPT
	if(TCP == tostring(GID)  and '04' == tostring(PID) and request == tostring(typeID))
	then
		subtree:add(fields.TCP04listenSocketId, tvb(offset, 2))
		offset = offset + 2
		subtree:add(fields.TCP04maxCon, tvb(offset, 2))
		offset = offset + 2
	end
	
	--6.10.9 CONNECT
	if(TCP == tostring(GID)  and '05' == tostring(PID) and request == tostring(typeID))
	then
		subtree:add(fields.TCP05socketId, tvb(offset, 2))
		offset = offset + 2
		subtree:add(fields.TCP05socketId, tvb(offset, 2))
		offset = offset + 2		
		
		local n = tvb(offset, 2)
		subtree:add(fields.UDPTCP01ipN, tvb(offset, 2))
		offset = offset + 2
		if('0004' == tostring(n))
		then
			subtree:add(fields.UDPTCP01ipv4, tvb(offset, 4))
			offset = offset + 4
		end
		if('0010' == tostring(n))
		then
			subtree:add(fields.UDPTCP01ipv6, tvb(offset, 16))
			offset = offset + 16	
		end
		
	end
	
	--6.10.10 CONFIGURE SOCKET
	if((UDP == tostring(GID) or TCP == tostring(GID))  and '06' == tostring(PID) and request == tostring(typeID))
	then
		subtree:add(fields.TCP06socketId, tvb(offset, 2))
		offset = offset + 2
		subtree:add(fields.TCP06paramId, tvb(offset, 2))
		offset = offset + 2
	end
	
	--6.10.11 READ SIGNAL QUALITY
	if(PHY == tostring(GID)  and '00' == tostring(PID) and response == tostring(typeID))
	then
		subtree:add(fields.PHY00sigQuality, tvb(offset, 1))
		offset = offset + 1
	end
	
	--6.10.12 READ DIAG RESULT
	if(PHY == tostring(GID)  and '01' == tostring(PID) and response == tostring(typeID))
	then
		subtree:add(fields.PHY01diagResult, tvb(offset, 1))
		offset = offset + 1
	end
	
	-- ACTIVATE TEST MODE
	-- TODO
	
	--SET PHY TX MODE
	-- TODO
	
	--6.11.1 SHUTDOWN
	if((UDP == tostring(GID) or TCP == tostring(GID))  and '07' == tostring(PID) and request == tostring(typeID))
	then
		subtree:add(fields.TCPUDP07socketId, tvb(offset, 2))
		offset = offset + 2
		subtree:add(fields.TCPUDP07typeId, tvb(offset, 1))
		offset = offset + 1		
	end
	
end
