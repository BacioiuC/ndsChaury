ground_tile_1 = 0
ground_tile_2 = 1

OFFSET_X = 128
OFFSET_Y = - 96
GRID_SIZE = 32

mapSizeX = 10
mapSizeY = 6

map = { }
function awake( )
	package.path = ""
	--dofile("test1.lua")
end

local topTable = { }


function start( )
	

	local temp = {
		sprite = Sprite.new( ),
		priority = 0,
	}
	temp.sprite:newSprite(0,  0, 256, 192, -15, 4, 5)
	temp.sprite:setTexture(ground_tile_1)
	--renderTable:add(temp.sprite, 1, 1, 1)
	table.insert(topTable, temp)
	generateGround( )
	
end

function generateGround( )
	for x = 1, mapSizeX do
		map[x] = { }
		for y = 1, mapSizeY do
			local temp = {
			sprite = Sprite.new( ),
			priority = 0,
			}
			temp.sprite:newSprite(x*32-32,  y*32-32, 32, 32, -15, 4, 5)
			texture = ground_tile_1;

			if(math.random(1,2) == 2) then
				texture = ground_tile_2
			end
			temp.sprite:setTexture(texture)
			map[x][y] = temp

		end
	end
end


function handleInput(_px, _py)

end

function renderTop( )
	for x = 1, mapSizeX do
		for y = 1, mapSizeY do
			map[x][y].sprite:update( );
		end
	end
end


function renderBottom( )

end



function renderTable(_table)
	
end




