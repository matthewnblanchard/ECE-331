% Matthew Blanchard
% ECE 331
% HW #1 Q5
% Due 1/26/2017
%
% Description: Tabulates and plots memory access rates for writing to
% memory block sizes of the powers of 10. Uses the program memspeed to
% calculate memory access times.

buf_size = 1;           % Buffer size
r_str = " ";            % Return string for a single call of memspeed
r_val = [0 0 0 0 0];    % Results of a single call of memspeed
r_raw = [];             % Results matrix for memspeed
r_fin = [];             % Computed results matrix, with size/time pairs

% Tabulate memory access times using memspeed
while (r_str(1) != 'E')       % First character of error message
        [dummy, r_str] = system(["./memspeed " num2str(buf_size)]);
        if (r_str(1) != 'E')
                r_val = strread(r_str, "%d");
                r_raw = [r_raw; r_val'];
        endif
        buf_size *= 10;
endwhile

% Convert raw memspeed.c table to size, time pairs
r_fin = zeros(rows(r_raw), 2);
for i = 1:rows(r_raw);
        r_fin(:, 1) = r_raw(:, 1);
        r_fin(:, 2) = r_raw(:, 4) - r_raw(:, 2);
        r_fin(:, 2) += (double(r_raw(:, 5) - r_raw(:, 3)) ./ 1e+9);
        r_fin(:, 2) = r_fin(:, 1) ./ r_fin(:, 2);
        r_fin(:, 2) ./= 1e+6;
endfor

% Plotting
fig = figure();
semilogx(r_fin(:, 1), r_fin(:,2), "marker", 'x', "linestyle", '-');
grid("minor", "on");
title("Memory Access Speed for Various Memory Block Sizes");
xlabel("Memory Block Size (bytes)");
ylabel("Memory Access Speed (Megabytes/second)");
saveas(fig, "plot.png");
