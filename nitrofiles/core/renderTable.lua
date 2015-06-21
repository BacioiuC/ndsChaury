renderTable = {}

function renderTable:init( )
	self._renderTable = { }
	self._sort = false
end

function renderTable:add(_v, _layer, _priority, _screen)
	local temp = {
		id = #self._renderTable + 1,
		object = _v,
		layer = _layer,
		priority = _priority,
		screen = _screen,
	}
	table.insert(self._renderTable, temp)

	self:sort( )
	return temp.id
end

function renderTable:setPriority(_id, _priority)
	local v = self._renderTable[_id]
	v.priority = _priority
end

function renderTable:getObject(_id)
	return self._renderTable[_id].object
end

function renderTable:sort( )
--[[
		local sortedEvaTable = { }
		if evaluationTable ~= nil then
			for i,v in spairs(evaluationTable, function(t,a,b) return t[b].value < t[a].value end) do
				table.insert(sortedEvaTable, v)
			end		

			-- first item in the table should be the most INTERESTING ONE! Return it
			if #sortedEvaTable ~= nil then
				return sortedEvaTable[1]
			end
		end	
--]]

		local sortedTable = { }
		for i,v in spairs(self._renderTable, function(t,a,b) return t[b].priority < t[a].priority end) do
			table.insert(sortedTable, v)
		end

		--self._renderTable = { }
		--self._renderTable = sortedTable
end

function renderTable:render(_screen)
	for i,v in ipairs(self._renderTable) do
		if v.screen == _screen then
			v.object:update( )
		end
	end
end

-----------------------------------------------------------------
-------------------- HELPFULL FUNCTIONS -------------------------
function spairs(t, order)
    -- collect the keys
    local keys = {}
    for k in pairs(t) do keys[#keys+1] = k end

    -- if order function given, sort by it by passing the table and keys a, b,
    -- otherwise just sort the keys 
    if order then
        table.sort(keys, function(a,b) return order(t, a, b) end)
    else
        table.sort(keys)
    end

    -- return the iterator function
    local i = 0
    return function()
        i = i + 1
        if keys[i] then
            return keys[i], t[keys[i]]
        end
    end
end