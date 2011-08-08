--function
function infinite_loop(fn, ...)
	--local tab = unpack(params);
	return function(...)
		while true do
			fn(...)
			coroutine.yield();
		end
	end
end

-- should pass args to
--, ...
function limited_loop(iterations, fn)

	assert( type(iterations) == "number");
	assert( type(fn) == "function");

	return function(...)
		local iter_left = iterations
		while iter_left > 0 do
			fn(...);
			iter_left = iter_left - 1;
			--log_info("iter left"..iter_left);
			--iter_left = coroutine.yield(iter_left - 1);
			--log_info("iter_lfet after yield",iter_left);
		end
	end


end


function wait_fn(delay)
			local time = 0;

			while time < delay do
				--print("Adding elapsed time ".. Engine:getElapsedTime().." to time "..time.."until delay "..delay);
				time = time + Engine:getElapsedTime();
				--print("New time before yield: "..time);
				coroutine.yield()
			end
			log_info("Waiting time finished");
end

function wait_fn2(delay)
			--local time = 0;

			while 0 < delay do
				--print("Adding elapsed time ".. Engine:getElapsedTime().." to time "..time.."until delay "..delay);
				delay = delay - Engine:getElapsedTime();
				--print("New time before yield: "..time);
				coroutine.yield()
			end
			log_info("Waiting time finished");
end


-- TODO sert a rien
function wait(delay)

	assert( type(delay) == "number");
	addBlockingTask(wait_fn,delay)
end



function onReach(progress)

    --print("LUA: level progression:"..Level:getUpperProgression());
	return (progress < MainState:getUpperProgression());

end

